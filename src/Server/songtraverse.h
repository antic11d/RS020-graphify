#ifndef SONGTRAVERSE_H
#define SONGTRAVERSE_H


#include "traversebehavior.h"
#include "qdebug.h"

class SongTraverse : public TraverseBehavior
{
public:
    virtual QVector<QPointer<Entity>> traverse(const QStringList &query, const QVector<QPointer<Entity>> &entires) const override;
};
#endif // SONGTRAVERSE_H
