#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>

#include "transport.h"
#include "thumbnailwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void btnSearchPressed();

private:
    Ui::MainWindow *ui;
    QWebEngineView *m_view;
    Transport *m_transport;
    QWidget *scroll;

    void initializeResources();
    void initializeRecommended();
    QString getThumbnail(QString url) const;
    QString getHtml(QString url) const;

};

#endif // MAINWINDOW_H
