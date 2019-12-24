#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QListWidget>
#include <QBrush>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QListWidgetItem *newItem = new QListWidgetItem;
//    newItem->setText(QString("Alkohola poplava"));
//    ui->listWidget->insertItem(1, newItem);

//    QGraphicsView *view1 = new QGraphicsView(ui->gvFirst);
    QPixmap pix("/home/andrija/RS020-graphify/src/resources/images/slika.png");
    pix = pix.scaled(ui->gvFirst->size());
    QPalette palette;
    palette.setBrush(QPalette::Base, pix);
    ui->gvFirst->setPalette(palette);



    QWebEngineView *view = new QWebEngineView(ui->graphicsView);
    view->load(QUrl(QStringLiteral("qrc:/view.html")));
    view->resize (ui->graphicsView->width (), ui->graphicsView->height ());
    view->show();

    m_transport = new Transport("localhost", 12345, true, this);
    // Should be done when CONNECT button is pressed
    if (m_transport->connectToHost()) {
        qDebug() << "Connected to server";
    } else {
        qDebug() << "Failed to connect";
    }

    // Should be done when SEND button is pressed
    // collect values from search bar
    if (m_transport->writeData("some_song", "some_genre", "some_performer")) {
        qDebug() << "Write succeeded";
    } else {
        qDebug() << "Write failed";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeResources()
{

}
