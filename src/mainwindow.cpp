#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_view(new QWebEngineView(this))
{
    setCentralWidget(m_view);
    m_view->load(QUrl(QStringLiteral("qrc:/index.html")));
}

MainWindow::~MainWindow()
{
    delete ui;
}
