#ifndef PERFORMERGENRETRAVERSE_H
#define PERFORMERGENRETRAVERSE_H

#include "traversebehavior.h"
#include "qdebug.h"

class PerformerGenreTraverse : public TraverseBehavior
{
public:
    virtual QVector<QString> traverse(const QStringList &query, const QVector<QPointer<Entity>> &entires) const override;
};

#endif // PERFORMERGENRETRAVERSE_H
