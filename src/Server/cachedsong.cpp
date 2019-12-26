#include "cachedsong.h"

CachedSong::CachedSong(QString title, QString url, QAtomicInt cnt)
    : m_title(title)
    , m_url(url)
    , m_cnt(cnt)
{

}

QAtomicInt CachedSong::getCnt()
{
    return m_cnt;
}

QString CachedSong::getTitle()
{
    return m_title;
}


QString CachedSong::getUrl()
{
    return m_url;
}

void CachedSong::increment()
{
    m_cnt++;
}
