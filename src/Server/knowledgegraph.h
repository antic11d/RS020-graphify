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
    QVector<QString> traverse(const QString &query) const;

private:
    QVector<QPair<QString, QString>> m_category {
        QPair(QString("music"), QString(":/data/query.json"))
    };
    QVector<QPointer<Entity>> m_entities;
    QFile *m_inFile = new QFile(this);

    void initalizeGraph();
    void parseJsonEntities(const QJsonArray &arr);
    template <typename T>
    QPointer<Entity> parse(const QJsonValue &v, QMap<QString, QPointer<Entity>> *entityMap, const QString &field);
    QVector<QString> packData(QVector<Song*> data) const;

};

#endif // KNOWLEDGEGRAPH_H
