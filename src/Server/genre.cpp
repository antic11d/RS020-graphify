#include "genre.h"

Genre::Genre(QString key, QString value, QPointer<Metadata> metadata, QObject *parent)
    : Entity(key, value, "GENRE", metadata, parent)
{

}
