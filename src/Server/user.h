#ifndef USER_H
#define USER_H

#include "entity.h"

class User : public Entity
{
    Q_OBJECT
public:
    User(QString key, QString value, QPointer<Metadata> metadata, QObject *parent = nullptr);
    void addSearch(const QPointer<Entity> &searchedSong);
};

#endif // USER_H
