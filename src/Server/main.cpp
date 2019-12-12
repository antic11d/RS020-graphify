#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server(9091);

    server.start();

    return a.exec();
}
