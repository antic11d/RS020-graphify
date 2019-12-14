#ifndef SERVER_H
#define SERVER_H

#include <QStringList>
#include <QTcpServer>
#include <QRandomGenerator>
#include <QDebug>
#include "knowledgegraph.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(int port, QObject *parent = nullptr);
    void start();

signals:

public slots:

private:
    void incomingConnection(qintptr handle) override;
    QStringList urls;
    int m_port;
    KnowledgeGraph *m_graph;
};

#endif // SERVER_H
