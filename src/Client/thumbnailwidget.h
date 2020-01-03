#ifndef THUMBNAILWIDGET_H
#define THUMBNAILWIDGET_H

#include <QWidget>
#include <QWebEngineView>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>

class ThumbnailWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit ThumbnailWidget(QString url, QWidget *parent = nullptr);

signals:
    void clicked(QString url);

private slots:
    void btnPlayPressed();

public:
    QString m_url;
    QWebEngineView *m_view;
    QPushButton *m_button;
    QLabel *m_info;

    QString getThumbnail(QString url) const;


};

#endif // THUMBNAILWIDGET_H
