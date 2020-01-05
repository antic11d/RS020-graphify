#ifndef PERFORMERSONGTRAVERSE_H
#define PERFORMERSONGTRAVERSE_H

#include "traversebehavior.h"

class PerformerSongTraverse : public TraverseBehavior
{
public:
    virtual QVector<QPointer<Entity>> traverse(const QStringList &query, const QVector<QPointer<Entity>> &entires) const override;
};

#endif // PERFORMERSONGTRAVERSE_H
