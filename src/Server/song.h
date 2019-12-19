#ifndef SONG_H
#define SONG_H

#include "entity.h"

#include <QObject>
#include <QString>

class Song : public Entity
{
    Q_OBJECT
public:
    Song(QString key, QString value, QPointer<Metadata> metadata = nullptr, QObject *parent = nullptr);
    ~Song();

    Song& operator=(Song other);
};

QDataStream &operator<<(QDataStream &out, const Song &s);
QDataStream &operator>>(QDataStream &out, Song &s);

#endif // SONG_H
