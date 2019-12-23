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
#include <algorithm>
#include <iterator>
#include "entity.h"
#include "performer.h"
#include "song.h"
#include "genre.h"
#include "gentrypoint.h"
#include "pentrypoint.h"
#include "sentrypoint.h"

class KnowledgeGraph : public QObject
{
    Q_OBJECT
public:
    KnowledgeGraph(const QString category, QObject *parent);
    void prepareQuery(const QString &query);
    QVector<QString> traverse(const QString &performer, const QString &title, const QString &genre) const;
    QVector<QString> traversePerformerGenre(const QString &performer, const QString &genre) const;

private:
    QVector<QPair<QString, QString>> m_category {
        QPair(QString("music"), QString(":/data/query.json"))
    };
    QVector<QPointer<Entity>> m_entities;
    QVector<QPointer<PEntryPoint>> m_pentries;
    QVector<QPointer<SEntryPoint>> m_sentries;
    QVector<QPointer<GEntryPoint>> m_gentries;
    QFile *m_inFile = new QFile(this);

    void initalizeGraph();
    void parseJsonEntities(const QJsonArray &arr);
    void connect_to_entry(const QPointer<Entity> e, QString flag, QMap<QString, QPointer<Entity>> *connectedEntities);
    template <typename T>
    QPointer<Entity> parse(const QJsonValue &v, QMap<QString, QPointer<Entity>> *entityMap, const QString &field);
    QVector<QString> packData(QVector<Song*> data) const;

};

#endif // KNOWLEDGEGRAPH_H
