#include "song.h"

Song::Song(QString key, QString value, QPointer<Metadata> metadata, QObject *parent)
    : Entity(key, value, "SONG", metadata, parent)
{

}

Song::~Song()
{}

Song& Song::operator=(Song other)
{
    std::swap(m_key, other.m_key);
    std::swap(m_value, other.m_value);
    std::swap(m_metadata, other.m_metadata);

    return *this;
}


QString Song::getRelatedEntity(QString edgeType) const
{
    foreach(auto &e, getEdges()) {
        if (e->getType() == edgeType)
            return e->getPointsTo()->getValue();
    }

    return "";
}
