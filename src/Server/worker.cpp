#include "worker.h"

Worker::Worker(int socketDescriptor, KnowledgeGraph *graph, MinHeap *cache, QObject *parent)
    : QThread(parent)
    , m_socketDescriptor(socketDescriptor)
{
    m_graph = graph;
    m_cache = cache;
}

void Worker::run()
{
    m_socket = new QTcpSocket();

    if (!m_socket->setSocketDescriptor(m_socketDescriptor)) {
        emit error(m_socket->error());
        return;
    }

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);

    qDebug() << "Client connected on handle" << m_socketDescriptor;
    auto song_titles = m_cache->read();
    QVector<QString> response;
    for (auto song_title : song_titles) {
        response.push_back(m_graph->findSong(song_title));
    }

    sendData(response);
    exec();
}

static QString bytesToString(QByteArray bytes)
{
    return QString::fromStdString(bytes.toStdString());
}

void Worker::readyRead()
{
    QByteArray buff = m_socket->readAll();

    QString stringified = bytesToString(buff);
    stringified = stringified.remove(QChar('\n'));
    //Stize Performer::Song::Genre
    //TODO kad stigne u formatu Performer::Song::Genre izvucemo pesmu ako ima
    qDebug() << "Got query" << stringified;
    QStringList query_params = stringified.split("::");
    QVector<QString> col_res;

    if(query_params[1] != "") {
        QString url = m_graph->findSongUrl(query_params[1]);
        if(url != nullptr) {
            m_cache->add(query_params[1], url);
        }
        QStringList query{query_params[1], query_params[3]};
        emit addUser(query_params[3], query_params[1]);
        QVector<QPointer<Entity>> col = m_graph->traverse(query, 9);
        for(auto song : col) {
            col_res.push_back(m_graph->findSong(song->getValue()));
        }
    }

    auto res = m_graph->traverseProcess(stringified);
    res += col_res;

    sendData(res);
}

bool Worker::sendData(QVector<QString> data)
{
    QDataStream stream(m_socket);
    stream << data;
    return true;
}

void Worker::disconnected()
{
    qDebug() << "Client disconnected from handle" << m_socketDescriptor;

    m_socket->deleteLater();
    exit(0);
}
