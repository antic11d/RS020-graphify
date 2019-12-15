#ifndef GENTRYPOINT_HPP
#define GENTRYPOINT_HPP

#include "entity.h"
#include "edge.h"
#include <QVector>

class GEntryPoint : public Entity
{
public:
    GEntryPoint(QString key, QString value, QObject *parent);
    ~GEntryPoint();

private:
    QVector<Edge*> m_edges;
};

#endif // GENTRYPOINT_HPP
