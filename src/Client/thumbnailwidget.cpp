#include "thumbnailwidget.h"

ThumbnailWidget::ThumbnailWidget(QString url, QString songTitle, QString performer, QString genre, QWidget *parent)
    : QGroupBox(parent)
    , m_url(url)
{
//    QSizePolicy policy(QSizePolicy::Expanding);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_view = new QWebEngineView(parent);
    m_view->resize(10, 150);
    m_view->setHtml(getThumbnail(url));
    m_view->setDisabled(true);

    m_button = new QPushButton(parent);
    m_button->resize(10, 40);
    m_button->setText("Play");

    connect(m_button, SIGNAL (pressed()), this, SLOT (btnPlayPressed()));

    m_info = new QLabel(parent);
    m_info->setText(performer+" - "+songTitle+", "+genre);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(m_view, 1);
    vbox->addWidget(m_info, 0, Qt::AlignHCenter);
    vbox->addWidget(m_button, 0, Qt::AlignHCenter);


    this->setMinimumSize(100, 100);
    this->setMaximumSize(300, 300);
    this->setLayout(vbox);
}

void ThumbnailWidget::btnPlayPressed()
{
    emit clicked(m_url);
}

QString ThumbnailWidget::getThumbnail(QString url) const
{
    QString html = QString("<!doctype html>\n")
            + "<html lang='en'>" + "\n"
                + "<head>"
                    + "<meta charset='utf-8'>" + "\n"
                    + "<style type='text/css'>" + "\n"
                        + "#thumbnail {" + "\n"
                            + "position: absolute;" + "\n"
                            + "top: 0;" + "\n"
                            + "left: 0;" + "\n"
                            + "width: 100%;" + "\n"
                            + "height: 100%;" + "\n"
                        + "}" + "\n"
                    + "</style>" + "\n"
                + "</head>" + "\n"
                + "<body>" + "\n"
                    "<img id=thumbnail src='https://img.youtube.com/vi/"+url+"/0.jpg'>"
                + "</body>" + "\n"
            + "</html>";

    return html;
}
