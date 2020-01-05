#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>

#include "transport.h"
#include "thumbnailwidget.h"
#include "logindialog.h"

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
    void btnPlayPressed(QString &url);
    void getUsername(QString &username);
    void initializeRecommended(QVector<QString> &urls);

    void btnLogOutPressed();

private:
    Ui::MainWindow *ui;
    QWebEngineView *m_view;
    Transport *m_transport;
    QWidget *scroll;
    bool loggedIn;
    QString m_username;


    QString getThumbnail(QString url) const;
    QString getHtml(QString url) const;
    void queryServer() const;
    void clearInput();

};

#endif // MAINWINDOW_H
