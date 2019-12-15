#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QPointer>
#include "edge.h"

class Edge;

class Entity : public QObject
{
    Q_OBJECT
public:
    Entity(QString key, QString value, QString type, QObject *parent = nullptr);
    ~Entity();
    void addEdge(QPointer<Edge> edge);
    QVector<QPointer<Edge>> getEdges() const;
    QString getKey() const;
    QString getValue() const;
    QString getType() const;

protected:
    QString m_key;
    QString m_value;
    QVector<QPointer<Edge>> m_edges;
    QString m_type;

};

#endif // ENTITY_H
