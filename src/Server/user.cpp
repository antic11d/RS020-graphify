#include "user.h"

User::User(QString key, QString value, QPointer<Metadata> metadata, QObject *parent)
    : Entity(key, value, "GENRE", metadata, parent)
{

}

void User::addSearch(const QPointer<Entity> &searchedSong)
{
    this->addEdge(QPointer(new Edge("LIKES", searchedSong, this)));
}
