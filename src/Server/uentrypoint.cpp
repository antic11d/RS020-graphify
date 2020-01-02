#include "uentrypoint.h"

UEntryPoint::UEntryPoint(QString key, QString value, QPointer<Metadata> metadata, QObject *parent)
    : Entity(key, value, "USER", metadata, parent)
{

}

UEntryPoint::~UEntryPoint()
{}
