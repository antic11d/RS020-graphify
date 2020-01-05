#ifndef GENRETRAVERSE_H
#define GENRETRAVERSE_H

#include "traversebehavior.h"

class GenreTraverse : public TraverseBehavior
{
public:
    virtual QVector<QPointer<Entity>> traverse(const QStringList &query, const QVector<QPointer<Entity>> &entires) const override;
};

#endif // GENRETRAVERSE_H
