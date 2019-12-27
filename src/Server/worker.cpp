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
//    qDebug() << stringified.lastIndexOf('\n');
//    stringified = stringified.trimmed();

//    if (stringified.contains("Want You Bad"))
//        stringified = QString("Want You Bad");
    qDebug() << "Got query" << stringified;
    QString search("Want You Bad");
//    QString url = m_graph->findSongUrl(search);
    QString url = m_graph->findSongUrl(QString("Want You Bad"));
    qDebug() << "ovde sam";
    qDebug() << "Ovo sam dobio kao rezultat mamu ti jebem" << url;
    if(url != nullptr) {
        m_cache->add(stringified, url);
    }


    //TODO nek bude stringified
    //Query se s fronta pravi tako da dodje Performer::Song::Genre
    //Ima pesma trap, nemoj se zbunis bato dobri
    QVector<QString> res = m_graph->traverseProcess("David Bowie::::");
    for (auto r : res) {
        qDebug() << "hopa " << r;
    }

    sendData(res);
}

bool Worker::sendData(QVector<QString> data)
{
    QDataStream stream(m_socket);
//    stream << QString("Picko\n").toUtf8();
    stream << data;
//    stream << QString("Picko\n").toUtf8();
//    QString packedData = data.toList().join("-");
//    if (m_socket->state() == QAbstractSocket::ConnectedState) {
//        qDebug() << "Sending graph data";
//        m_socket->write(packedData.toUtf8());

//        return m_socket->waitForBytesWritten();
//    } else
//        return false;
    return true;
}

void Worker::disconnected()
{
    qDebug() << "Client disconnected from handle" << m_socketDescriptor;

    m_socket->deleteLater();
    exit(0);
}
