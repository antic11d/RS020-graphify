#include "minheap.h"

MinHeap::MinHeap(const QVector<CachedSong> &initial_songs)
{
    for(auto song : initial_songs) {
        inCache.insert(song.getTitle(), song);
        minHeap.push(song);
    }
}

MinHeap::MinHeap(const QVector<CachedSong> &&initial_songs)
{
    for(auto song : initial_songs) {
        inCache.insert(song.getTitle(), song);
        minHeap.push(song);
    }
}

void MinHeap::add(const QString &title, const QString &url)
{
    m_mutex.lock();
    auto it = inCache.find(title);
    if (it == inCache.end()) {
        qDebug() << "nisam naso brata";
        minHeap.pop();
        minHeap.push(CachedSong(title, url, 1));
    }
    else {
        qDebug() << "naso sam brata";
        auto toUpdatrSong = inCache.find(title);
        toUpdatrSong.value().increment();
        minHeap = std::priority_queue<CachedSong, QVector<CachedSong>, comparator> ();
        for (auto it : inCache) {
            minHeap.push(it);
        }
    }
    m_mutex.unlock();
}

void MinHeap::print()
{
    while(!minHeap.empty()){
        auto top = minHeap.top();
        qDebug() << top.getTitle();
        minHeap.pop();
    }
}

QVector<QString> MinHeap::read()
{
    QVector<QString> res;
    for (auto song : inCache) {
        res.push_back(song.getUrl());
    }
    return res;
}
