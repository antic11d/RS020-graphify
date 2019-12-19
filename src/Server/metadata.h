#ifndef METADATA_H
#define METADATA_H

#include <QObject>

class Metadata : public QObject
{
    Q_OBJECT
public:
    explicit Metadata(QString value, QObject *parent = nullptr);
    QString getStrVal() const;
private:
    QString m_strVal;
};

#endif // METADATA_H
