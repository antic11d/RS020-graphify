#ifndef SERVER_H
#define SERVER_H

#include <QStringList>
#include <QTcpServer>
#include <QRandomGenerator>
#include <QDebug>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(int port, QObject *parent = nullptr);
    void start();

signals:

public slots:

protected:
    void incomingConnection(qintptr handle) override;
    QStringList urls;
    int m_port;
};

#endif // SERVER_H
