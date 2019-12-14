#ifndef PERFORMER_H
#define PERFORMER_H

#include "entity.h"

class Performer : public Entity
{
    Q_OBJECT
public:
    Performer(QString key, QString value, QObject *parent = nullptr);
};

#endif // PERFORMER_H
