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

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection); // DirectConnection zbog tredova
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection); // DirectConnection zbog tredova

    qDebug() << "Client connected on handle" << m_socketDescriptor;
    sendData(m_cache->read());

    exec(); // loop
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
    //TODO kad stigne u formatu Performer::Song::Genre izvucemo pesmu ako ima
    qDebug() << "Got query" << stringified;

    QString url = m_graph->findSongUrl(stringified);
    if(url != nullptr) {
        m_cache->add(stringified, url);
    }


    //TODO nek bude stringified
    //Query se s fronta pravi tako da dodje Performer::Song::Genre
    //Ima pesma trap, nemoj se zbunis bato dobri
    QVector<QPointer<Entity>> res = m_graph->traverseProcess("Shakira::::");

//    sendData(res);
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
