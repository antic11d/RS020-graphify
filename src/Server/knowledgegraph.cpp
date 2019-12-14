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

std::pair<bool, QString> KnowledgeGraph::parse(const QJsonValue &v, const QSet<QString> &knownIds, const QString &field)
{
    QString id = v.toObject().value(field).toString();
    int idx = id.lastIndexOf(QString("/"));
    QString parsedId = id.right(id.length() - idx - 1);

    if (knownIds.contains(parsedId))
        return { false, "" };

    return { true, parsedId };
}


void KnowledgeGraph::parseJsonEntities(const QJsonArray &arr)
{
    QSet<QString> knownIds;

    foreach(const QJsonValue &v, arr) {
        const auto [iTitle, title] = parse(v, knownIds, "title");
        if (iTitle) {
            QString titleLabel = v.toObject().value("titleLabel").toString();
            knownIds.insert(title);
            m_entities.insert(0, new Song(title, titleLabel, this));
        }

        const auto [iPerformer, performer] = parse(v, knownIds, "performer");
        if (iPerformer) {
            QString performerLabel = v.toObject().value("performerLabel").toString();
            knownIds.insert(title);
            m_entities.insert(0, new Performer(performer, performerLabel, this));
        }

        const auto [iGenre, genre] = parse(v, knownIds, "genre");
        if (iGenre) {
            QString genreLabel = v.toObject().value("genreLabel").toString();
            knownIds.insert(genre);
            m_entities.insert(0, new Genre(genre, genreLabel, this));
        }

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


