#ifndef PERFORMERTRAVERSE_H
#define PERFORMERTRAVERSE_H

#include "traversebehavior.h"
#include "qdebug.h"

class PerformerTraverse : public TraverseBehavior
{
public:
    virtual QVector<QString> traverse(const QStringList &query, const QVector<QPointer<Entity>> &entires) const override;
};

#endif // PERFORMERTRAVERSE_H


