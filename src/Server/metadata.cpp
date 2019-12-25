#include "metadata.h"

Metadata::Metadata(QString value, QString url, QObject *parent)
    : QObject(parent)
    , m_strVal(value)
    , m_url(url)
{

}

QString Metadata::getStrVal() const
{
    return m_strVal;
}

QString Metadata::getUrl() const
{
    return m_url;
}

