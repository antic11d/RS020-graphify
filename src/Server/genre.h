#ifndef GENRE_H
#define GENRE_H

#include "entity.h"

class Genre : public Entity
{
    Q_OBJECT
public:
    Genre(QString key, QString value, QPointer<Metadata> metadata, QObject *parent = nullptr);
};

#endif // GENRE_H
