#include "genretraverse.h"

QVector<QPointer<Entity>> GenreTraverse::traverse(const QStringList &query, const QVector<QPointer<Entity>> &entires) const {

    QString genre = query[0];
    QVector<QPointer<Entity>> res;
    auto starting_entry = entires[0];



    for(auto e_genre : starting_entry->getEdges()) {
        if (e_genre->getPointsTo()->getValue() == genre) {
            auto searchedGenre = e_genre->getPointsTo();
            for (auto song_e : searchedGenre->getEdges()) {
                if (song_e->getType() == "TYPE_FOR") {
                    res.push_back(song_e->getPointsTo());
                }
            }
        }
    }

    return res;
}
