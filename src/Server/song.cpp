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

QDataStream &operator<<(QDataStream &out, const Song &s)
{
    out << s.getKey() << s.getValue() << s.getMetadataValue();
    return out;
}

QDataStream &operator>>(QDataStream &in, Song &s)
{
    QString key;
    QString value;
    QString metadata;

    in >> key >> value >> metadata;

    s = Song(key, value, QPointer(new Metadata(metadata)), nullptr);

    return in;
}


