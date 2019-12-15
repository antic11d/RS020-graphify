#include "song.h"

Song::Song(QString key, QString value, QObject *parent)
    : Entity(key, value, "SONG", parent)
{

}

Song::~Song()
{}
