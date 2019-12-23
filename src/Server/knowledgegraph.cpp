#include "knowledgegraph.h"

void KnowledgeGraph::initalizeGraph()
{
    qDebug() << "Reading file on path " << m_inFile->fileName();

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

void KnowledgeGraph::connect_to_entry(const QPointer<Entity> e, QString flag, QMap<QString, QPointer<Entity>> *connectedEntities) {

    if(e == nullptr || connectedEntities->contains(e->getKey()))
        return;

    if (flag == "s") {
        m_sentries[0]->addEdge(QPointer(new Edge("CONTAINS", e, this)));
        qDebug() << "\t" << m_sentries[0]->getValue() << "CONTAINS " << e->getKey() << "\n";
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
        QString label = v.toObject().value(field+"Label").toString();
        Entity* parsed;
        if (field == "title") {
            parsed = new T(parsedId, label, QPointer(new Metadata("url")), this);
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
    m_pentries.push_back(QPointer(new PEntryPoint("P1", "P1")));
    m_sentries.push_back(QPointer(new SEntryPoint("S1", "S1")));
    m_gentries.push_back(QPointer(new GEntryPoint("G1", "G1")));
    QMap<QString, QPointer<Entity>> entityMap;
    QMap<QString, QPointer<Entity>> connectedEntities;
    QSet<QString> knownEntites;
    foreach(const QJsonValue &v, arr) {
        auto song = parse<Song>(v, &entityMap, "title");
        auto performer = parse<Performer>(v, &entityMap, "performer");
        auto genre = parse<Genre>(v, &entityMap, "genre");

        connect_to_entry(song, "s", &connectedEntities);
        connect_to_entry(performer, "p", &connectedEntities);
        connect_to_entry(genre, "g", &connectedEntities);


//        Connect the dots
        performer->addEdge(QPointer(new Edge("SINGS", song, this)));
        song->addEdge(QPointer(new Edge("SINGED_BY", performer, this)));
        if (genre != nullptr) {
            song->addEdge(QPointer(new Edge("TYPE_OF", genre, this)));
            genre->addEdge(QPointer(new Edge("TYPE_FOR", song, this)));
        }
    }
/*
    foreach(const auto& e, entityMap.values()) {
        if (e->getType() == "PERFORMER") {
            qDebug() << e->getType() << e->getKey() << e->getValue();

            foreach(const auto& edge, e->getEdges())
                qDebug() << "\t" << edge->getType() << edge->getPointsTo()->getValue();
        }
    }

    qDebug() << "====================================";

    foreach(const auto& e, entityMap.values()) {
        if (e->getType() == "SONG") {
            qDebug() << e->getType() << e->getKey() << e->getValue();

            foreach(const auto& edge, e->getEdges())
                qDebug() << "\t" << edge->getType() << edge->getPointsTo()->getValue();
        }
    }

    qDebug() << "====================================";

    foreach(const auto& e, entityMap.values()) {
        if (e->getType() == "GENRE") {
            qDebug() << e->getType() << e->getKey() << e->getValue();

            foreach(const auto& edge, e->getEdges())
                qDebug() << "\t" << edge->getType() << edge->getPointsTo()->getValue();
        }
    }*/
}

KnowledgeGraph::KnowledgeGraph(const QString category, QObject *parent)
    : QObject(parent)

{
    for (auto pair : m_category) {
        if (pair.first == category)
            m_inFile->setFileName(pair.second);
    }

    initalizeGraph();
    prepareQuery("Shakira::Waka::hip hop music");
}

QVector<QString> KnowledgeGraph::packData(QVector<Song*> data) const
{
    qDebug() << "Packing data...";
    QVector<QString> result;
    foreach(auto &s, data) {
        result.push_back(QString(
                          s->getValue()+","
                         +s->getMetadataValue()+","
                         +s->getRelatedEntity("TYPE_OF")+","
                         +s->getRelatedEntity("PERFORMED_BY")
                                 ));
    }

    qDebug() << "Packed:" << result;


    return result;
}

void KnowledgeGraph::prepareQuery(const QString &query) {
    QStringList query_params = query.split("::");
    auto res = traverse(query_params[0], query_params[1], query_params[2]);
}

QVector<QString> KnowledgeGraph::traverse(const QString &performer, const QString &title, const QString &genre) const
{
    return traversePerformerGenre(performer, genre);
}

QVector<QString> KnowledgeGraph::traversePerformerGenre(const QString &performer, const QString &genre) const
{

    QVector<QString> mock_up;
    QVector<QPointer<Edge>> e_performers;
    QVector<QPointer<Edge>> e_songs;
    QVector<QPointer<Entity>> _performers;
    QVector<QVector<Edge>> _songs;
    auto starting_entry = m_pentries[0];

    auto all_performers = starting_entry->getEdges();
    std::copy_if(all_performers.begin(),all_performers.end(), std::back_inserter(e_performers) ,
                 [&performer](QPointer<Edge> e){return e->getPointsTo()->getValue() == performer;});

    std::transform(e_performers.cbegin(), e_performers.cend(),
                   std::back_inserter(_performers),
                   [](QPointer<Edge> e){return e->getPointsTo();});

    QVector<QPointer<Edge>> all_songs;
    for (auto p : _performers) {
        auto all_p_edges = p->getEdges();
        std::copy_if(all_p_edges.begin(),all_p_edges.end(), std::back_inserter(all_songs) ,
                     [](QPointer<Edge> e){
                        return e->getType() == "SINGS";
                    });
    }

//    QVector<QPointer<Edge>> all_valid_songs;
//    std::copy_if(all_songs.begin(),all_songs.end(), std::back_inserter(all_valid_songs) ,
//                 [&genre](QPointer<Edge> song){
//        for (auto song_edge : song->getPointsTo()->getEdges()) {
//            return song_edge->getType() == "TYPE_OF" && song_edge->getPointsTo()->getValue() == genre;
//        }
//    });


//    for (auto i : e_performers) {
//        qDebug() << i->getPointsTo()->getValue() << " ";
//        for (auto e : i->getPointsTo()->getEdges()) {
//            if (e->getType() == "SINGS") {
//                auto song = e->getPointsTo();
//                for (auto &s : song->getEdges()) {
//                    if (s->getType() == "TYPE_OF" && s->getPointsTo()->getValue() == genre) {
//                        qDebug() << song->getValue();
//                    }
//                }
//            }

//        }
//    }

    for (auto song : all_songs) {
        for(auto song_edge : song->getPointsTo()->getEdges()) {
            if (song_edge->getType() == "TYPE_OF" && song_edge->getPointsTo()->getValue() == genre) {
                mock_up.push_back(song->getPointsTo()->getValue());
            }
        }
    }
    for (auto v : mock_up){
        qDebug() << v;
    }
    return mock_up;
}



