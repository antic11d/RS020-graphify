#ifndef MINHEAP_H
#define MINHEAP_H

#include <queue>
#include <QVector>
#include <QMap>
#include <QMutex>
#include <QDebug>
#include "cachedsong.h"

struct comparator {
 bool operator()(CachedSong &s1, CachedSong &s2) {
 return s1.getCnt() > s2.getCnt();
 }
};

class MinHeap
{
public:
    MinHeap(const QVector<CachedSong> &initial_songs);
    MinHeap(const QVector<CachedSong> &&initial_songs);
    void add(const QString &title, const QString &url);
    QVector<QString> read();
    void print();
private:
    QMutex m_mutex;
    std::priority_queue<CachedSong, QVector<CachedSong>, comparator> minHeap;
    QMap<QString, CachedSong> inCache;
};

#endif // MINHEAP_H
