#ifndef WORKER_H
#define WORKER_H

#include <QtNetwork>
#include <QThread>
#include <QTcpSocket>

class Worker : public QThread
{
    Q_OBJECT
public:
    Worker(int socketDescriptor, const QString &url, QObject *parent = nullptr);

    void run() override;

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

private:
    int m_socketDescriptor;
    QString m_url;
    QTcpSocket *m_socket;
};

#endif // WORKER_H
