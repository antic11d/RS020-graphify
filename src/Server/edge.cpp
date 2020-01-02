#include "edge.h"

Edge::Edge(QString type, QPointer<Entity> pointsTo, QObject *parent, int strength)
    : QObject(parent)
    , m_type(type)
    , m_strength(strength)
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

void Edge::reinforce()
{
    m_strength++;
}

int Edge::getStrength()
{
    return m_strength;
}
