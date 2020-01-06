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
}

bool Transport::writeData(QString query) const
{
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        m_socket->write((query).toUtf8());

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

QVector<QString> Transport::parseData(QString &string) const
{
    QVector<QString> result;
    foreach (auto s, string.split("::"))
        result.push_back(s);
    return result;
}

void Transport::readData()
{
    QDataStream socketStream(m_socket);
    QVector<QString> urls;
    for (;;) {
    socketStream.startTransaction();
    socketStream >> urls;

    if (socketStream.commitTransaction()) {
        emit dataReady(urls);
    }
    else
        break;
    }
}
