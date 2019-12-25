#ifndef METADATA_H
#define METADATA_H

#include <QObject>

class Metadata : public QObject
{
    Q_OBJECT
public:
    explicit Metadata(QString value, QString url = "", QObject *parent = nullptr);
    QString getStrVal() const;
    QString getUrl() const;
private:
    QString m_strVal;
    QString m_url;
};

#endif // METADATA_H
