#ifndef TRAVERSEBEHAVIOR_H
#define TRAVERSEBEHAVIOR_H

#include <QString>
#include <QVector>
#include <QStringList>
#include "entity.h"

class TraverseBehavior
{
public:
    virtual QVector<QPointer<Entity>> traverse(const QStringList &query, const QVector<QPointer<Entity>> &entires) const = 0;
};

#endif // TRAVERSEBEHAVIOR_H
