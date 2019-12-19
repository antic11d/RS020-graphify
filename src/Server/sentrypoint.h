#ifndef SENTRYPOINT_H
#define SENTRYPOINT_H

#include <QObject>
#include <QString>
#include <QVector>

#include "entity.h"
#include "edge.h"

class SEntryPoint : public Entity
{
public:
    SEntryPoint(QString key, QString value, QPointer<Metadata> metadata = nullptr, QObject *parent = nullptr);
};

#endif // SENTRYPOINT_H
