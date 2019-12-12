#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QWebEngineFullScreenRequest>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_view(new QWebEngineView(this))
{
    setCentralWidget(m_view);

    m_view->load(QUrl(QStringLiteral("qrc:/view.html")));
//    m_view->
}

MainWindow::~MainWindow()
{
    delete ui;
}
