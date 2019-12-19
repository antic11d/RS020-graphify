#include "metadata.h"

Metadata::Metadata(QString value, QObject *parent)
    : QObject(parent)
    , m_strVal(value)
{

}

QString Metadata::getStrVal() const
{
    return m_strVal;
}
