#ifndef SERVER_H
#define SERVER_H

#include <QString>
#include <QStringList>
#include <QTcpServer>
#include <QRandomGenerator>
#include <QDebug>
#include "knowledgegraph.h"
#include "minheap.h"
#include "cachedsong.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(int port, QObject *parent = nullptr);
    ~Server() override;
    void start();

signals:

public slots:

private:
    void incomingConnection(qintptr handle) override;
    QStringList urls;
    int m_port;
    MinHeap *cache;
    KnowledgeGraph *m_graph;
};

#endif // SERVER_H
