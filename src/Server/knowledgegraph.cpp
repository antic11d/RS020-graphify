#include "knowledgegraph.h"

//Helper functions
int prepareArray(QStringList &query_params) {
    QString res;
    QMutableStringListIterator it(query_params);

    while(it.hasNext() == true) {
        auto value = it.next();
        if (value == "") {
            res.push_back("0");
            it.remove();
        }
        else {
            res.push_back("1");
        }
    }
    res.remove(3, 1);
    bool ok;
    return res.toInt(&ok, 2);
}

QPair<QStringList, int> prepareQuery(const QString &query) {
    QStringList query_params = query.split("::");
    int t_case = prepareArray(query_params);
    return QPair<QStringList, int>(query_params, t_case);
}

QVector<QString> KnowledgeGraph::packForSending(QVector<QPointer<Entity>> &response, QString performer, QString genre)
{
   QVector<QString> res;
   for (auto song : response) {
        auto data = findSong(song->getValue());
        QString songData = "";
        songData += song->getMetadata()->getUrl() + "::";
        songData += song->getValue() + "::";
        songData += performer != "" ? performer : data[2];
        songData += "::";
        songData += genre != "" ? genre : data[3];
        res.push_back(songData);
   }

   return res;

}

QVector<QString> KnowledgeGraph::getRecommendation(QString performer, QString genre)
{
    QVector<QPointer<Entity>> res;
    QStringList to_send;
    if (performer != "") {
        to_send.push_back(performer);
        res += traverse(to_send, 4);
    }
    to_send.clear();
    if (genre != "") {
        to_send.push_back(genre);
        res += traverse(to_send, 1);
    }

    return packForSending(res, "", "");
}

QVector<QString> KnowledgeGraph::prepForSending(QVector<QPointer<Entity>> &res, QStringList query_params, const int &t_case)
{
    QVector<QString> result;
    QVector<QString> data;
    QVector<QString> recommendation;
    switch (t_case) {
        case 1:
            result = packForSending(res, "", query_params[0]);
            break;
        case 2:
            if (res.size() == 0)
                break;
            result = packForSending(res, "", "");
            data = findSong(res[0]->getValue());
            recommendation = getRecommendation(data[2], data[3]);
            result += recommendation;
            break;
        case 3:
            if (res.size() > 0)
            {
                result = packForSending(res, "", query_params[1]);
                data = findSong(res[0]->getValue());
                recommendation = getRecommendation("", data[3]);
                result += recommendation;
            }
            else {
                recommendation = getRecommendation("", query_params[1]);
                result += recommendation;
            }
            break;
        case 4:
            result = packForSending(res, query_params[0], "");
            break;
        case 5:
            result = packForSending(res, query_params[0], query_params[1]);
            recommendation = getRecommendation(query_params[0], query_params[1]);
            result += recommendation;
            break;
        case 6:
            if (res.size() > 0)
            {
                result = packForSending(res, query_params[0], "");
                data = findSong(res[0]->getValue());
                recommendation = getRecommendation(data[2], "");
                result += recommendation;
            }
            else
            {
                recommendation = getRecommendation(query_params[0], "");
                result += recommendation;
            }
            break;
        default:
            break;
    }
    return result;
}


void KnowledgeGraph::initalizeGraph()
{
    if (!m_inFile->exists()) {
        qDebug() << "File doesnt exists";
        return;
    }

    m_inFile->open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray data = m_inFile->readAll();
    m_inFile->close();

    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
    if (doc.isNull()) {
        qDebug() << "Parse failed";
    }
    QJsonObject obj = doc.object();
    QJsonValue value = obj.value("data");
    QJsonArray jsonArray = value.toArray();

    parseJsonEntities(jsonArray);
}

void KnowledgeGraph::connectToEntry(const QPointer<Entity> e, QString flag, QMap<QString, QPointer<Entity>> *connectedEntities) {

    if(e == nullptr || connectedEntities->contains(e->getKey()))
        return;

    if (flag == "s") {
        m_sentries[0]->addEdge(QPointer(new Edge("CONTAINS", e, this)));
    }
    if (flag == "g") {
        m_gentries[0]->addEdge(QPointer(new Edge("CONTAINS", e, this)));
    }
    if (flag == "p") {
        m_pentries[0]->addEdge(QPointer(new Edge("CONTAINS", e, this)));
    }

    connectedEntities->insert(e->getKey(), e);
}


template <typename T>
QPointer<Entity> KnowledgeGraph::parse(const QJsonValue &v, QMap<QString, QPointer<Entity>>* entityMap, const QString &field)
{
    QString id = v.toObject().value(field).toString().trimmed();
    int idx = id.lastIndexOf(QString("/"));
    QString parsedId = id.right(id.length() - idx - 1);

    if (parsedId == "")
        return nullptr;

    if (!entityMap->contains(parsedId)) {
        QString label = v.toObject().value(field+"Label").toString().toLower();

        Entity* parsed;
        if (field == "title") {
            QString ytLink = v.toObject().value("YouTube_video_ID").toString();
            parsed = new T(parsedId, label, QPointer(new Metadata("url", ytLink)), this);
        } else {
            parsed = new T(parsedId, label, nullptr, this);
        }

        entityMap->insert(parsedId, parsed);
        m_entities.push_back(QPointer(parsed));

        return QPointer<Entity>(parsed);
    } else {
        return entityMap->value(parsedId);
    }
    return nullptr;
}

void KnowledgeGraph::parseJsonEntities(const QJsonArray &arr)
{
    Entity *p = new PEntryPoint("P1", "P1", nullptr, this);
    m_pentries.push_back(QPointer(p));
    p = new SEntryPoint("S1", "S1", nullptr, this);
    m_sentries.push_back(QPointer(p));
    p = new GEntryPoint("G1", "G1", nullptr, this);
    m_gentries.push_back(QPointer(p));
    p = new UEntryPoint("U1", "U1", nullptr, this);
    m_uentries.push_back(QPointer(p));
    QMap<QString, QPointer<Entity>> entityMap;
    QMap<QString, QPointer<Entity>> connectedEntities;
    QSet<QString> knownEntites;
    foreach(const QJsonValue &v, arr) {
        auto song = parse<Song>(v, &entityMap, "title");
        auto performer = parse<Performer>(v, &entityMap, "performer");
        auto genre = parse<Genre>(v, &entityMap, "genre");

        connectToEntry(song, "s", &connectedEntities);
        connectToEntry(performer, "p", &connectedEntities);
        connectToEntry(genre, "g", &connectedEntities);

        performer->addEdge(QPointer(new Edge("SINGS", song, this)));
        song->addEdge(QPointer(new Edge("SINGED_BY", performer, this)));
        if (genre != nullptr) {
            song->addEdge(QPointer(new Edge("TYPE_OF", genre, this)));
            genre->addEdge(QPointer(new Edge("TYPE_FOR", song, this)));
        }
    }
}

KnowledgeGraph::KnowledgeGraph(const QString category, QObject *parent)
    : QObject(parent)

{
    for (auto pair : m_category) {
        if (pair.first == category)
            m_inFile->setFileName(pair.second);
    }

    initalizeGraph();

    newUser("mica", "changes");
    newUser("mica", "run it!");
    newUser("mica", "whenever, wherever");
    newUser("mica", "turn up the radio");
    newUser("nidza", "whenever, wherever");
    newUser("nidza", "changes");
    newUser("nidza", "changes");
    newUser("mica", "turn up the radio");
    newUser("nidza", "turn up the radio");
    newUser("andrija", "changes");

}

QVector<QString> KnowledgeGraph::traverseProcess(const QString &query) {
    QPair<QStringList, int> prepared = prepareQuery(query);
    QString username = prepared.first.last();
    existing_users.insert(username);
    prepared.first.pop_back();
    QVector<QPointer<Entity>> res = traverse(prepared.first, prepared.second);
//    if (res.size() == 0)
//       return QVector<QString>();
    auto result = prepForSending(res, prepared.first, prepared.second);
    QString searched;
    if (result.size() > 0) {
        searched = result[0];
        result.pop_front();
    }
    std::sort( result.begin(), result.end() );
    result.erase( std::unique( result.begin(), result.end() ), result.end());
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(result.begin(), result.end(), g);
    if (result.size() > 0)
        result.push_front(searched);
    return result;
}



QVector<QPointer<Entity>> KnowledgeGraph::traverse(QStringList &query_params, const int &t_case) {
    QVector<QPointer<Entity>> res;
    PerformerGenreTraverse pgT;
    PerformerTraverse pT;
    SongTraverse sT;
    CollaborativeFIltering cT;
    GenreTraverse gT;
    PerformerSongTraverse psT;
    SongGenreTraverse sgT;
    TraverseBehavior *t = nullptr;
    switch (t_case) {
        case 1:
            t = &gT;
            res = t->traverse(query_params, m_gentries);
            break;
        case 2:
            t = &sT;
            res = t->traverse(query_params, m_sentries);
            break;
        case 3:
            t = &sgT;
            res = t->traverse(query_params, m_sentries);
            break;
        case 4:
            t = &pT;
            res = t->traverse(query_params, m_pentries);
            break;
        case 5:
            t = &pgT;
            res = t->traverse(query_params, m_pentries);
            break;
        case 6:
            t = &psT;
            res = t->traverse(query_params, m_sentries);
            break;
        case 9:
            t = &cT;
            res = t->traverse(query_params, m_sentries);
        default:
            break;
    }
    return res;
}


void KnowledgeGraph::addUser(const QString &username, const QString &passwd) {
    Entity *new_user = new User(username, passwd, nullptr);
    m_entities.push_back(QPointer(new_user));
    m_uentries[0]->addEdge(QPointer(new Edge("CONTAINS", new_user)));
}


void KnowledgeGraph::strengthenGraph(const QString &username, const QString &title)
{
    QPointer<Entity> searchedSong = nullptr;
    QPointer<Entity> user = nullptr;
    auto song_e = m_sentries[0];
    auto user_e = m_uentries[0];
    for (auto tmpUser : user_e->getEdges()) {
        if (tmpUser->getPointsTo()->getValue() == username) {
            user = tmpUser->getPointsTo();

            for (auto user_edge : user->getEdges()) {
                if (user_edge->getType() == "LIKES") {
                    auto likedSong = user_edge->getPointsTo();
                    if (likedSong->getValue() == title) {
                        user_edge->reinforce();
                        return;
                    }
                }
            }
        }
    }
    for (auto song : song_e->getEdges()){
        if(song->getPointsTo()->getValue() == title) {
            searchedSong = song->getPointsTo();
        }
    }
    if (user != nullptr && searchedSong != nullptr)
    {
        user->addEdge(QPointer(new Edge("LIKES", searchedSong, this, 1)));
        searchedSong->addEdge(QPointer(new Edge("LIKED_BY", user, this)));
    }
}

QVector<QString> KnowledgeGraph::findSong(const QString &title)
{
    QString performer = "";
    QString genre = "";
    QString url = "";
    auto song_e = m_sentries[0];
    for(auto song : song_e->getEdges()) {
        if (song->getPointsTo()->getValue() == title) {
            url = song->getPointsTo()->getMetadata()->getUrl();
            for (auto edge : song->getPointsTo()->getEdges()) {
                if (edge->getType() == "SINGED_BY" && performer == "") {
                    performer = edge->getPointsTo()->getValue();
                }
                if (edge->getType() == "TYPE_OF" && genre == "") {
                    genre = edge->getPointsTo()->getValue();
                }
                if (performer != "" && genre != "")
                    break;
            }
        }
    }

    return QVector<QString>{url, title, performer, genre};
}


QString KnowledgeGraph::findSongUrl(const QString &title)
{
    auto song_e = m_sentries[0];
    for(auto song : song_e->getEdges()) {
        if (song->getPointsTo()->getValue() == title) {
            return song->getPointsTo()->getMetadata()->getUrl();
        }
    }
    return nullptr;

}

void KnowledgeGraph::newUser(QString username, QString title)
{
    if (!existing_users.contains(username))
    {
        addUser(username, username);
        existing_users.insert(username);
    }

    strengthenGraph(username, title);
}

