#include "performersongtraverse.h"

QVector<QPointer<Entity>> PerformerSongTraverse::traverse(const QStringList &query, const QVector<QPointer<Entity>> &entires) const {

    QString song = query[1];
    QString performer = query[0];
    QVector<QPointer<Entity>> res;
    auto starting_entry = entires[0];

    for(auto e_song : starting_entry->getEdges()) {
        if (e_song->getPointsTo()->getValue() == song) {
            auto searchedSong = e_song->getPointsTo();
            for (auto e_performer : searchedSong->getEdges()) {
                if (e_performer->getType() == "SINGED_BY" && e_performer->getPointsTo()->getValue() == performer) {
                    res.push_back(searchedSong);
                }
            }
        }
    }

    return res;
}
