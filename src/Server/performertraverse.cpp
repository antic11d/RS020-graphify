#include "performertraverse.h"

QVector<QPointer<Entity>> PerformerTraverse::traverse(const QStringList &query, const QVector<QPointer<Entity>> &entires) const {
    QString performer = query[0];
    QVector<QPointer<Edge>> e_performers;
    QVector<QPointer<Entity>> res;
    auto starting_entry = entires[0];



    auto all_performers = starting_entry->getEdges();
    std::copy_if(all_performers.begin(),all_performers.end(), std::back_inserter(e_performers) ,
                 [&performer](QPointer<Edge> e){return e->getPointsTo()->getValue() == performer;});



    QVector<QPointer<Edge>> all_songs;
    for (auto p : e_performers) {
        auto all_p_edges = p->getPointsTo()->getEdges();
        std::copy_if(all_p_edges.begin(),all_p_edges.end(), std::back_inserter(all_songs) ,
                     [](QPointer<Edge> e){
                        return e->getType() == "SINGS";
                    });
    }



    for (auto song : all_songs) {
        res.push_back(song->getPointsTo());
    }

    return res;
}
