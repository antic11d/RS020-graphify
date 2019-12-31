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
#include <QPair>
#include <algorithm>
#include <iterator>
#include "entity.h"
#include "performer.h"
#include "song.h"
#include "genre.h"
#include "gentrypoint.h"
#include "pentrypoint.h"
#include "sentrypoint.h"
#include "performergenretraverse.h"
#include "performertraverse.h"
#include "songtraverse.h"
//#include "cachedsong.h"
//#include "minheap.h"

class KnowledgeGraph : public QObject
{
    Q_OBJECT
public:
    KnowledgeGraph(const QString category, QObject *parent);
    QVector<QString> traverse(const QStringList &query_params, const int &t_case) const;
    QVector<QString> traverseProcess(const QString &query);
    QString findSongUrl(const QString &title);

private:
    QVector<QPair<QString, QString>> m_category {
        QPair(QString("music"), QString(":/data/query.json")),
        QPair(QString("big_data"), QString(":/data/big_sample.json"))
    };
    QVector<QPointer<Entity>> m_entities;
    QVector<QPointer<Entity>> m_pentries;
    QVector<QPointer<Entity>> m_sentries;
    QVector<QPointer<Entity>> m_gentries;
    QFile *m_inFile = new QFile(this);

    void initalizeGraph();
    void parseJsonEntities(const QJsonArray &arr);
    void connectToEntry(const QPointer<Entity> e, QString flag, QMap<QString, QPointer<Entity>> *connectedEntities);
    template <typename T>
    QPointer<Entity> parse(const QJsonValue &v, QMap<QString, QPointer<Entity>> *entityMap, const QString &field);
//    QVector<QString> packData(QVector<Song*> data) const;

};

#endif // KNOWLEDGEGRAPH_H
