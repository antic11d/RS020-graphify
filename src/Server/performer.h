#ifndef PERFORMER_H
#define PERFORMER_H

#include "entity.h"

class Performer : public Entity
{
    Q_OBJECT
public:
    Performer(QString key, QString value, QPointer<Metadata> metadata, QObject *parent = nullptr);
    ~Performer();
};

#endif // PERFORMER_H
