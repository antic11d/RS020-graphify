#include "pentrypoint.h"

PEntryPoint::PEntryPoint(QString key, QString value, QObject *parent)
    : Entity(key, value, "PERFORMER", parent)
{

}

PEntryPoint::~PEntryPoint()
{}
