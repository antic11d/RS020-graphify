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

std::pair<bool, QString> KnowledgeGraph::parse(const QJsonValue &v, const QMap<QString, QPointer<Entity>> &entityMap, const QString &field)
{
    QString id = v.toObject().value(field).toString();

    if (id == "")
        return { false, "" };

    int idx = id.lastIndexOf(QString("/"));
    QString parsedId = id.right(id.length() - idx - 1);

    if (entityMap.contains(parsedId))
        return { false, parsedId };

    return { true, parsedId };
}


void KnowledgeGraph::parseJsonEntities(const QJsonArray &arr)
{
    QMap<QString, QPointer<Entity>> entityMap;

    foreach(const QJsonValue &v, arr) {
        const auto [iTitle, title] = parse(v, entityMap, "title");
        if (iTitle) {
            QString titleLabel = v.toObject().value("titleLabel").toString();
            QPointer<Entity> song(new Song(title, titleLabel, this));
            entityMap.insert(title, song);
            m_entities.push_back(song);
        }

        const auto [iPerformer, performer] = parse(v, entityMap, "performer");
        if (iPerformer) {
            QString performerLabel = v.toObject().value("performerLabel").toString();
            QPointer<Entity> perf(new Performer(performer, performerLabel, this));
            entityMap.insert(performer, perf);
            m_entities.push_back(new Performer(performer, performerLabel, this));
        }

        const auto [iGenre, genre] = parse(v, entityMap, "genre");
        if (iGenre) {
            QString genreLabel = v.toObject().value("genreLabel").toString();
            QPointer<Entity> g(new Genre(genre, genreLabel, this));
            entityMap.insert(genre, g);
            m_entities.push_back(new Genre(genre, genreLabel, this));
        }

        // Connect the dots

        auto P = entityMap.take(performer);
        auto S = entityMap.take(title);


        P->addEdge(QPointer(new Edge("SINGS", S, this)));
        S->addEdge(QPointer(new Edge("SINGED_BY", P, this)));
//        P->addEdge(QPointer(new Edge("SINGS", S, this)));

//        if (iGenre) {
//            auto G = entityMap.take(genre);
//        }

        qDebug() << P->getValue() << " "
                 << P->getEdges().at(0)->getType()
                 << P->getEdges().at(0)->getPointsTo()->getValue();
    }

//    qDebug() << knownIds;
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


