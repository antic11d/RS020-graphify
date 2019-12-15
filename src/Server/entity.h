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
    Entity(QString key, QString value, QObject *parent = nullptr);
    ~Entity();
    void addEdge(QPointer<Edge> edge);
    QVector<QPointer<Edge>> getEdges() const;
    QString getKey() const;
    QString getValue() const;

protected:
    QString m_key;
    QString m_value;
    QVector<QPointer<Edge>> m_edges;

};

#endif // ENTITY_H
