#include "pentrypoint.h"

PEntryPoint::PEntryPoint(QString key, QString value, QPointer<Metadata> metadata, QObject *parent)
    : Entity(key, value, "PERFORMER", metadata, parent)
{

}

PEntryPoint::~PEntryPoint()
{}
