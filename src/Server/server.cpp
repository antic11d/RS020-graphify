#include "server.h"
#include "worker.h"

Server::Server(int port, QObject *parent)
    : QTcpServer(parent)
    , m_port(port)
{
    urls << tr("https://www.youtube.com/embed/skq59BfjkyM")
         << tr("https://www.youtube.com/embed/u-ndajHaih8")
         << tr("https://www.youtube.com/embed/vgmRgE1k8Ek&t=2222s");

    cache = new MinHeap(QVector<CachedSong> {
                            CachedSong (QString("changes"), QString("xMQ0Ryy01yE"), 1),
                            CachedSong (QString("run it!"), QString("w6QGe-pXgdI"), 1),
                            CachedSong (QString("this love"), QString("XPpTgCho5ZA"), 1),
                            CachedSong (QString("whenever, wherever"), QString("weRHyjj34ZE"), 1)
                            });
}

void Server::start()
{
    m_graph = new KnowledgeGraph(QString("big_data"), this);
    qDebug() << "Uspeo Server";
    if (!this->listen(QHostAddress::Any, m_port)) {
        qDebug() << "Could not start server on port" << m_port;
    } else {
        qDebug() << "Listening on port" << m_port;
    }
}

void Server::incomingConnection(qintptr handle)
{
    qDebug() << "Handle" << handle << "connecting...";

    Worker *worker = new Worker(handle, m_graph, cache, this);
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(worker, SIGNAL(addUser(QString, QString)), m_graph, SLOT(newUser(QString, QString)));
    worker->start();
}

Server::~Server()
{
    this->close();
}
