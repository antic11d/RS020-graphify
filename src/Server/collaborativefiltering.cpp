#include "collaborativefiltering.h"

QVector<QPointer<Entity>> CollaborativeFIltering::traverse(const QStringList &query, const QVector<QPointer<Entity>> &entires) const {
    QString title = query[0];
    QString username = query[1];
    QVector<QPointer<Entity>> res;
    QVector<QVector<QPointer<Entity>>> songs;
    auto starting_entry = entires[0];
    for(auto tmp_song_edge : starting_entry->getEdges())
    {
        if(tmp_song_edge->getPointsTo()->getValue() == title)
        {
            qDebug() << tmp_song_edge->getPointsTo()->getValue();
            auto searched_song = tmp_song_edge->getPointsTo();
            auto users = find_all_users(searched_song);

            for (auto user : users) {
                if (user->getValue() != username) {
                    songs.push_back(find_all_liked_songs(user));
                }
            }
        }
    }

    for (auto i : songs)
    {
        for (auto j : i)
        {
            res.push_back(j);
        }
    }

    return res;
}

QVector<QPointer<Entity>> CollaborativeFIltering::find_all_users(QPointer<Entity> song) const
{
    QVector<QPointer<Entity>> res;
    for (auto liked : song->getEdges())
    {
        if (liked->getType() == "LIKED_BY") {
           res.push_back(liked->getPointsTo());
        }
    }

    return res;
}

QVector<QPointer<Entity>> CollaborativeFIltering::find_all_liked_songs(const QPointer<Entity> user) const
{
    QVector<QPointer<Entity>> songs;
    for (auto liked_song : user->getEdges()) {
        if(liked_song->getType() == "LIKES") {
            songs.push_back(liked_song->getPointsTo());
        }
    }

    return songs;
}
