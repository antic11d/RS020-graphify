#ifndef SONG_H
#define SONG_H

#include "entity.h"

#include <QObject>
#include <QString>

class Song : public Entity
{
    Q_OBJECT
public:
    Song(QString key, QString value, QObject *parent = nullptr);
    ~Song();
};

#endif // SONG_H
