#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QWebSocket>
#include <QObject>

class Transport : public QObject
{
    Q_OBJECT
public:
    explicit Transport(const QUrl &url, bool debug = false, QObject *parent = nullptr);

signals:
    void closed();

private slots:
    void onConnected();
    QString onMessageRecieved(QString msg);

private:
    int SERVER_PORT = 12345;
    QUrl m_url;
    QWebSocket m_socket;
    bool m_debug;
};

#endif // TRANSPORT_H
