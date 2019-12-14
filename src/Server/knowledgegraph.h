#ifndef KNOWLEDGEGRAPH_H
#define KNOWLEDGEGRAPH_H

#include <QString>
#include <QObject>
#include <QPair>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QVector>
#include "entity.h"
#include "performer.h"
#include "song.h"
#include "genre.h"

class KnowledgeGraph : public QObject
{
    Q_OBJECT
public:
    KnowledgeGraph(const QString category, QObject *parent);

private:
    QVector<QPair<QString, QString>> m_category {
        QPair(QString("music"), QString(":/data/query.json"))
    };
    QVector<Entity*> m_entities;
    QFile *m_inFile = new QFile(this);
//    QJsonArray m_jsonArray;
    void initalizeGraph();
    void parseJsonEntities(const QJsonArray &arr);
    std::pair<bool, QString> parse(const QJsonValue &v, const QSet<QString> &knownIds, const QString &field);
//    std::pair<bool, QString> parseTitle(const QJsonValue &v, const QSet<QString> &knownIds);
//    std::pair<bool, QString> parseGenre(const QJsonValue &v, const QSet<QString> &knownGenres);
};

#endif // KNOWLEDGEGRAPH_H
