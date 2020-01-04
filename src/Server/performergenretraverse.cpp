#include "performergenretraverse.h"

QVector<QPointer<Entity>> PerformerGenreTraverse::traverse(const QStringList &query, const QVector<QPointer<Entity>> &entires) const {
    QString performer = query[0];
    QString genre = query[1];

    QVector<QPointer<Entity>> res;
    QVector<QPointer<Edge>> e_performers;
    QVector<QPointer<Edge>> e_songs;
    QVector<QPointer<Entity>> _performers;
    QVector<QVector<Edge>> _songs;
    auto starting_entry = entires[0];

    auto all_performers = starting_entry->getEdges();
    std::copy_if(all_performers.begin(),all_performers.end(), std::back_inserter(e_performers) ,
                 [&performer](QPointer<Edge> e){return e->getPointsTo()->getValue() == performer;});

    std::transform(e_performers.cbegin(), e_performers.cend(),
                   std::back_inserter(_performers),
                   [](QPointer<Edge> e){return e->getPointsTo();});

    QVector<QPointer<Edge>> all_songs;
    for (auto p : _performers) {
        auto all_p_edges = p->getEdges();
        std::copy_if(all_p_edges.begin(),all_p_edges.end(), std::back_inserter(all_songs) ,
                     [](QPointer<Edge> e){
                        return e->getType() == "SINGS";
                    });
    }

    for (auto song : all_songs) {
        for(auto song_edge : song->getPointsTo()->getEdges()) {
            if (song_edge->getType() == "TYPE_OF" && song_edge->getPointsTo()->getValue() == genre) {
                res.push_back(song->getPointsTo());
            }
        }
    }


    return res;
}
