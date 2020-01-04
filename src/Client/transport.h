#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QTcpSocket>
#include <QUrl>
#include <QObject>
#include <QDataStream>
#include "../Server/song.h"

class Transport : public QObject
{
    Q_OBJECT
public:
    explicit Transport(const QString &hostname, quint16 port = 12345, bool debug = false, QObject *parent = nullptr);
    QVector<QString> parseData(QString& string) const;

signals:
    void closed();
    void dataReady(QVector<QString> &urls);

public slots:
      bool writeData(QString query) const;
      void readData();
      bool connectToHost() const;

private:
    QString m_hostname;
    quint16 m_port;
    QTcpSocket *m_socket;
    QDataStream m_in;
    bool m_debug;
};

#endif // TRANSPORT_H
