#include "transport.h"
#include <QDebug>

Transport::Transport(const QUrl &url, bool debug, QObject *parent)
    : QObject(parent)
    , m_url(url)
    , m_debug(debug)
{
    if (m_debug)
        qDebug() << "Socket on url: " << url;

    connect(&m_socket, &QWebSocket::connected, this, &Transport::onConnected);
    connect(&m_socket, &QWebSocket::disconnected, this, &Transport::closed);
    m_socket.open(QUrl(url));
}

void Transport::onConnected()
{
    if (m_debug)
        qDebug() << "Socket connected";

    connect(&m_socket, &QWebSocket::textMessageReceived,
            this, &Transport::onMessageRecieved);

    m_socket.sendTextMessage(QStringLiteral("Give me trail"));
}

QString Transport::onMessageRecieved(QString msg)
{
    if (m_debug)
        qDebug() << "Recieved: " << msg;

    m_socket.close();

    return msg;
}
