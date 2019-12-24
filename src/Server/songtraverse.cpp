#include "songtraverse.h"


//TODO must return link instead of name
QVector<QString> SongTraverse::traverse(const QStringList &query, const QVector<QPointer<Entity>> &entires) const {
    QString song = query[0];
//    QVector<QPointer<Edge>> e_performers;
    QVector<QString> res;
    auto starting_entry = entires[0];

    for(auto e_song : starting_entry->getEdges()) {
        if (e_song->getPointsTo()->getValue() == song)
            res.push_back(e_song->getPointsTo()->getMetadata()->getUrl());
    }

    return res;
}
