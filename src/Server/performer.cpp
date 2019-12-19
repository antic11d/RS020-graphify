#include "performer.h"

Performer::Performer(QString key, QString value, QPointer<Metadata> metadata, QObject *parent)
    : Entity(key, value, "PERFORMER", metadata, parent)
{

}

Performer::~Performer()
{}

