#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QString>

class Entity : public QObject
{
    Q_OBJECT
public:
    Entity(QString key, QString value, QObject *parent = nullptr);

protected:
    QString m_key;
    QString m_value;

};

#endif // ENTITY_H
