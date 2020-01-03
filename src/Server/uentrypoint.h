#ifndef UENTRYPOINT_H
#define UENTRYPOINT_H


#include "entity.h"
#include "edge.h"
#include <QVector>

class UEntryPoint : public Entity
{
public:
    UEntryPoint(QString key, QString value, QPointer<Metadata> metadata = nullptr, QObject *parent = nullptr);
    ~UEntryPoint();

private:
    QVector<Edge*> m_edges;
};

#endif // UENTRYPOINT_H
