#ifndef CACHEDSONG_H
#define CACHEDSONG_H

#include <QString>
#include <QVector>
#include <QAtomicInt>
#include "song.h"

class CachedSong
{
public:
    CachedSong(QString title, QString url, QAtomicInt m_cnt = 1);
    void increment();
    QAtomicInt getCnt();
    QString getTitle();
    QString getUrl();

private:
    QString m_title;
    QString m_url;
    QAtomicInt m_cnt;
};

#endif // CACHEDSONG_H
