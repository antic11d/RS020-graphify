#include "worker.h"

Worker::Worker(int socketDescriptor, KnowledgeGraph *graph, QObject *parent)
    : QThread(parent)
    , m_socketDescriptor(socketDescriptor)
{
    m_graph = graph;
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

//    qDebug() << "Got query" << stringified;

    //TODO start traversal through graph
    auto data = m_graph->traverse(stringified);

    sendData(data);
}

bool Worker::sendData(QVector<QString> data)
{
    QString packedData = data.toList().join("-");
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        qDebug() << "Sending graph data";
        m_socket->write(packedData.toUtf8());

        return m_socket->waitForBytesWritten();
    } else
        return false;
}

void Worker::disconnected()
{
    qDebug() << "Client disconnected from handle" << m_socketDescriptor;

    m_socket->deleteLater();
    exit(0);
}
