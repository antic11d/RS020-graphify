#ifndef SONGGENRETRAVERSE_H
#define SONGGENRETRAVERSE_H

#include "traversebehavior.h"

class SongGenreTraverse : public TraverseBehavior
{
public:
    virtual QVector<QPointer<Entity>> traverse(const QStringList &query, const QVector<QPointer<Entity>> &entires) const override;
};

#endif // SONGGENRETRAVERSE_H
