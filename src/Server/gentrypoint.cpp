#include "gentrypoint.h"

GEntryPoint::GEntryPoint(QString key, QString value, QPointer<Metadata> metadata, QObject *parent)
    : Entity(key, value, "GENRE", metadata, parent)
{

}

GEntryPoint::~GEntryPoint()
{}
