#include "entity.h"

Entity::Entity(QString key, QString value, QObject *parent)
    : QObject(parent)
    , m_key(key)
    , m_value(value)
{}

Entity::~Entity()
{}

void Entity::addEdge(QPointer<Edge> edge)
{
    m_edges.push_back(edge);
}

QVector<QPointer<Edge>> Entity::getEdges() const
{
    return m_edges;
}

QString Entity::getKey() const
{
    return m_key;
}

QString Entity::getValue() const
{
    return m_value;
}

