#ifndef THUMBNAILWIDGET_H
#define THUMBNAILWIDGET_H

#include <QWidget>
#include <QWebEngineView>
#include <QPushButton>

class ThumbnailWidget : public QWebEngineView
{
    Q_OBJECT
public:
    explicit ThumbnailWidget(QString url, QWidget *parent = nullptr);

public:
    QString m_url;

    QString getThumbnail(QString url) const;

signals:

};

#endif // THUMBNAILWIDGET_H
