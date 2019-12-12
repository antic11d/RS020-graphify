#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWebEngineView>
#include <QWebEngineSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_view(new QWebEngineView(this))
{
    setCentralWidget(m_view);
    initializeResources();

    m_view->load(QUrl(QStringLiteral("qrc:/view.html")));
//    m_view->
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeResources()
{

}
