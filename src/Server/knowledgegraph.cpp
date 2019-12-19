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
    QMap<QString, QPointer<Entity>> entityMap;
    QSet<QString> knownEntites;
    foreach(const QJsonValue &v, arr) {
        auto song = parse<Song>(v, &entityMap, "title");
        auto performer = parse<Performer>(v, &entityMap, "performer");
        auto genre = parse<Genre>(v, &entityMap, "genre");

//        Connect the dots
        performer->addEdge(QPointer(new Edge("SINGS", song, this)));
        song->addEdge(QPointer(new Edge("SINGED_BY", performer, this)));
        if (genre != nullptr) {
            song->addEdge(QPointer(new Edge("TYPE_OF", genre, this)));
            genre->addEdge(QPointer(new Edge("TYPE_FOR", song, this)));
        }
    }

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
}


