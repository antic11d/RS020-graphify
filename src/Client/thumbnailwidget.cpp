#include "thumbnailwidget.h"

ThumbnailWidget::ThumbnailWidget(QString url, QWidget *parent)
    : QWidget(parent)
    , m_url(url)
{
    m_webView = new QWebEngineView(parent);
    m_webView->resize(20, 80);
    m_webView->setHtml(getThumbnail(url));
    m_webView->setDisabled(true);
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
