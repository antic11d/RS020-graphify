#include "songtraverse.h"


QVector<QPointer<Entity>> SongTraverse::traverse(const QStringList &query, const QVector<QPointer<Entity>> &entries) const {
    QString song = query[0];
    QVector<QPointer<Entity>> res;
    auto starting_entry = entries[0];

    qDebug() << "U traversu " << starting_entry->getEdges().size();

    for(auto e_song : starting_entry->getEdges()) {
//        if(e_song->getPointsTo() != nullptr)
//            qDebug() << e_song->getPointsTo()->getType();
//        else
//            qDebug() << "kurcina od nulla";
        if (e_song->getPointsTo()->getValue() == song)
            res.push_back(e_song->getPointsTo());
    }

    qDebug() << "Izaso sam ";

    return res;
}
