#include "transport.h"
#include <QDebug>

Transport::Transport(const QString& hostname, quint16 port, bool debug, QObject *parent)
    : QObject(parent)
    , m_hostname(hostname)
    , m_port(port)
    , m_socket(new QTcpSocket(this))
    , m_debug(debug)
{
    m_in.setDevice(m_socket);
    m_in.setVersion(QDataStream::Qt_5_5);

    connect(m_socket, &QIODevice::readyRead, this, &Transport::readData);
    if (m_debug)
        qDebug() << "Transport up";
}

// Helper serialization
static QByteArray intToArray(qint32 source)
{
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}

//TODO should be attached as button SEND callback
bool Transport::writeData(QString song, QString genre, QString performer) const
{
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        m_socket->write((song+","+genre+","+performer).toUtf8());

        return m_socket->waitForBytesWritten();
    } else
        return false;
}

//TODO should be attached as button CONNECT callback
bool Transport::connectToHost() const
{
    m_socket->abort(); // interrupt in progress request if there is one
    m_socket->connectToHost(m_hostname, m_port);

    if (m_debug)
        qDebug() << "Contacting server: " << m_hostname << m_port;

    return m_socket->waitForConnected();
}

void Transport::readData()
{
//    QString msg = m_socket->readAll();

//    qDebug() << "Got graph data" << msg;

    QDataStream socketStream(m_socket);
    QVector<QString> urls;
//    QString url;
    for (;;) {
    socketStream.startTransaction();
    socketStream >> urls;
    if (socketStream.commitTransaction()) {
        qDebug() << "Received :";
        for (auto url : urls) {
            qDebug() << url;
        }
    }

    else
        break;
    }

}
