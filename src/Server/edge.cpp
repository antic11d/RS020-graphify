#include "edge.h"

Edge::Edge(QString type, QPointer<Entity> pointsTo, QObject *parent)
    : QObject(parent)
    , m_type(type)
{
    m_pointsTo = pointsTo;
}

Edge::~Edge()
{}

QPointer<Entity> Edge::getPointsTo() const
{
    return m_pointsTo;
}

QString Edge::getType() const
{
    return m_type;
}
