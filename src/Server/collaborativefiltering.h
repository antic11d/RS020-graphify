#ifndef COLLABORATIVEFILTERING_H
#define COLLABORATIVEFILTERING_H

#include "traversebehavior.h"
#include "entity.h"
#include <QPointer>
#include <QVector>
#include <QDebug>
class CollaborativeFIltering : public TraverseBehavior
{
private:
    QVector<QPointer<Entity>> find_all_users(QPointer<Entity> song) const;
    QVector<QPointer<Entity>> find_all_liked_songs(const QPointer<Entity> user) const;
public:
    virtual QVector<QString> traverse(const QStringList &query, const QVector<QPointer<Entity>> &entires) const override;
};

#endif // COLLABORATIVEFILTERING_H
