#include "songgenretraverse.h"

QVector<QPointer<Entity>> SongGenreTraverse::traverse(const QStringList &query, const QVector<QPointer<Entity>> &entires) const {

    QString song = query[0];
    QString genre = query[1];
    QVector<QPointer<Entity>> res;
    auto starting_entry = entires[0];

    qDebug() << "u funkicji " << song << " " << genre;

    for(auto e_song : starting_entry->getEdges()) {
        if (e_song->getPointsTo()->getValue() == song) {
            auto searchedSong = e_song->getPointsTo();
            for (auto e_genre : searchedSong->getEdges()) {
                if (e_genre->getType() == "TYPE_OF" && e_genre->getPointsTo()->getValue() == genre) {
                    res.push_back(searchedSong);
                }
            }
        }
    }

    return res;
}
