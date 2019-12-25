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
    QString getRelatedEntity(QString edgeType) const;

    Song& operator=(Song other);
};

#endif // SONG_H
