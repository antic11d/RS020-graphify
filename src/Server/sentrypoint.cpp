#include "sentrypoint.h"

SEntryPoint::SEntryPoint(QString key, QString value, QPointer<Metadata> metadata, QObject *parent)
    : Entity(key, value, "SONG", metadata, parent)
{

}
