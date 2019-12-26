#ifndef EDGE_H
#define EDGE_H

#include <QObject>
#include "entity.h"

class Entity;

class Edge : public QObject
{
    Q_OBJECT
public:
    explicit Edge(QString type, QPointer<Entity> pointsTo, QObject *parent = nullptr, int strength = 0);
    ~Edge();
    QString getType() const;
    QPointer<Entity> getPointsTo() const;

private:
    QString m_type;
    QPointer<Entity> m_pointsTo;
    int m_strength;
};

#endif // EDGE_H
