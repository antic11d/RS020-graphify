#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(QString("Alkohola poplava"));
    ui->listWidget->insertItem(1, newItem);

    QWebEngineView *view = new QWebEngineView(ui->graphicsView);
    view->load(QUrl(QStringLiteral("qrc:/view.html")));
    view->resize (ui->graphicsView->width (), ui->graphicsView->height ());
    view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeResources()
{

}
