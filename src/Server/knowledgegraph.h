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
#include "uentrypoint.h"
#include "gentrypoint.h"
#include "pentrypoint.h"
#include "sentrypoint.h"
#include "performergenretraverse.h"
#include "performertraverse.h"
#include "songtraverse.h"
#include "collaborativefiltering.h"
#include "cachedsong.h"
#include "minheap.h"
#include "user.h"

class KnowledgeGraph : public QObject
{
    Q_OBJECT
public:
    KnowledgeGraph(const QString category, QObject *parent);

    QVector<QPointer<Entity>> traverse(const QStringList &query_params, const int &t_case) const;
    QVector<QPointer<Entity>> traverseProcess(const QString &query);
    QVector<QString> collaborative(const QString &username, const QString &title);
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
    QVector<QPointer<Entity>> m_uentries;
    QMap<QString, QPointer<User>> m_users;
    QFile *m_inFile = new QFile(this);

    void initalizeGraph();
    void parseJsonEntities(const QJsonArray &arr);
    void connectToEntry(const QPointer<Entity> e, QString flag, QMap<QString, QPointer<Entity>> *connectedEntities);
    template <typename T>
    QPointer<Entity> parse(const QJsonValue &v, QMap<QString, QPointer<Entity>> *entityMap, const QString &field);
//    QVector<QString> packData(QVector<Song*> data) const;
    void addUser(const QString &username, const QString &passwd);
    void strengthenGraph(const QString &username, const QString &title);

};

#endif // KNOWLEDGEGRAPH_H
