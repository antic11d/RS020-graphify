#include "worker.h"

Worker::Worker(int socketDescriptor, const QString &url, QObject *parent)
    : QThread(parent)
    , m_socketDescriptor(socketDescriptor)
    , m_url(url)
{
}

void Worker::run()
{
    qDebug() << "Starting thread";
    m_socket = new QTcpSocket();

    if (!m_socket->setSocketDescriptor(m_socketDescriptor)) {
//        emit error(m_socket->error());
        return;
    }

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection); // DirectConnection zbog tredova
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection); // DirectConnection zbog tredova

    qDebug() << m_socketDescriptor << " Client connected";

    exec(); // loop
}

void Worker::readyRead()
{
    QByteArray data = m_socket->readAll();
    qDebug() << "Got data in: " << data;

//    m_socket->write(m_url.toUtf8());
    m_socket->write(data);
}

void Worker::disconnected()
{
    qDebug() << "Client disconnected";

    m_socket->deleteLater();
    exit(0);
}
