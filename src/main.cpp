#include "mainwindow.h"
#include <QApplication>

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QJsonObject>

#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QJsonObject obj
    {
          {"property1", 1},
          {"property2", 2}
      };


    QApplication a(argc, argv);
    MainWindow w;

    QMediaPlayer *player = new QMediaPlayer;
    QVideoWidget *widget = new QVideoWidget;

    player->setVideoOutput(widget);
    player->setMedia(QUrl::fromLocalFile("/Users/dimitrijeantic/Downloads/majaberovic.mp4"));


    widget->setGeometry(100, 100, 300, 400);
    widget->show();

    player->play();

    qDebug() << player->state();

    return a.exec();
}
