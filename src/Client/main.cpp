#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.setWindowTitle ("Graphify");
    mainWindow.resize(1024, 768);
    mainWindow.show();

    return app.exec();
}
