#include "songtraverse.h"


QVector<QPointer<Entity>> SongTraverse::traverse(const QStringList &query, const QVector<QPointer<Entity>> &entires) const {
    QString song = query[0];
    QVector<QPointer<Entity>> res;
    auto starting_entry = entires[0];

    for(auto e_song : starting_entry->getEdges()) {
        if (e_song->getPointsTo()->getValue() == song)
            res.push_back(e_song->getPointsTo());
    }

    return res;
}
