#include "minheap.h"

MinHeap::MinHeap(QVector<CachedSong> &initial_songs)
{
    for(auto song : initial_songs) {
        inCache.insert(song.getTitle(), song);
        minHeap.push(song);
    }
}

void MinHeap::add(const QString &title)
{
    m_mutex.lock();
    auto it = inCache.find(title);
    if (it == inCache.end()) {
        qDebug() << "nisam naso brata";
        minHeap.pop();
        minHeap.push(CachedSong(title, title, 1));
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
