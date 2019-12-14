#include "entity.h"

Entity::Entity(QString key, QString value, QObject *parent)
    : QObject(parent)
    , m_key(key)
    , m_value(key)
{}

