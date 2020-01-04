#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWebEngineView>
#include <QWebEngineSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_transport = new Transport("192.168.1.108", 12345, true, this);

    if (m_transport->connectToHost()) {
        qDebug() << "Connected to server";
    } else {
        qDebug() << "Failed to connect";
    }

    loggedIn = false;

    connect(ui->btnSearch, SIGNAL (pressed()), this, SLOT (btnSearchPressed()));
    connect(m_transport, SIGNAL (dataReady(QVector<QString>&)), this, SLOT (initializeRecommended(QVector<QString>&)));
}

void MainWindow::initializeRecommended(QVector<QString> &urls)
{
    m_view = new QWebEngineView(ui->graphicsView);
//    m_view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_view->resize(ui->graphicsView->width(), ui->graphicsView->height());
    if (urls.length() > 0) {
        m_view->setHtml(getHtml(urls[0].split("::")[0]));
        m_view->show();
    } else {
        m_view->hide();
//        m_view->close();
    }

    scroll = new QWidget;
    scroll->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    scroll->setLayout(new QVBoxLayout(ui->scrollArea));

    ui->scrollArea->setWidget(scroll);

    QLayout *layout = scroll->layout();

    QVector<ThumbnailWidget*> widgets;
    for (auto url : urls) {
        auto parsedData = m_transport->parseData(url);
        //url::song::perfomer::genre
        ThumbnailWidget *view = new ThumbnailWidget(parsedData[0], parsedData[1], parsedData[2], parsedData[3], ui->scrollArea);

        connect(view, SIGNAL (clicked(QString&)), this, SLOT (btnPlayPressed(QString&)));

        view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->setAlignment(Qt::AlignRight);
        layout->addWidget(view);
    }
}

void MainWindow::btnPlayPressed(QString &url)
{
    m_view->setHtml(getHtml(url));
}

void MainWindow::clearInput()
{
    ui->txtSong->clear();
    ui->txtGenre->clear();
    ui->txtPerformer->clear();
}

void MainWindow::btnSearchPressed()
{
    if (ui->txtSong->text() == "" && ui->txtGenre->text() == "" && ui->txtPerformer->text() == "")
        return;

    if (!loggedIn) {
        LoginDialog *login = new LoginDialog(this);
        connect(login, SIGNAL (acceptLogin(QString&)), this, SLOT (getUsername(QString&)));

        login->exec();

        loggedIn = true;
    }
    queryServer();
    clearInput();
}

void MainWindow::queryServer() const
{
    QString genre = ui->txtGenre->text().trimmed().toLower();
    QString performer = ui->txtPerformer->text().trimmed().toLower();
    QString song = ui->txtSong->text().trimmed().toLower();

    QString query = performer + "::" + song + "::" + genre + "::" + m_username;

    qDebug() << "About to send query:" << query;

    if (m_transport->writeData(query)) {
        qDebug() << "Write succeeded";
        m_transport->readData();
    } else {
        qDebug() << "Write failed";
    }
}

void MainWindow::getUsername(QString &username)
{
    m_username = username;
}

QString MainWindow::getHtml(QString url) const
{
    QString html = QString("<!doctype html>\n")
            + "<html lang='en'>" + "\n"
                + "<head>"
                    + "<meta charset='utf-8'>" + "\n"
                    + "<style type='text/css'>" + "\n"
                        + "#ytplayer {" + "\n"
                            + "position: absolute;" + "\n"
                            + "top: 0;" + "\n"
                            + "left: 0;" + "\n"
                            + "width: 100%;" + "\n"
                            + "height: 100%;" + "\n"
                        + "}" + "\n"
                    + "</style>" + "\n"
                + "</head>" + "\n"
                + "<body>" + "\n"
                 +   "<iframe" + "\n"
                   +     "id='ytplayer'" + "\n"
                    +    "src='https://www.youtube.com/embed/"+url+"'" + "\n"
                   +     "frameborder='0'" + "\n"
                    +    "allowfullscreen>" + "\n"
                 +   "</iframe>" + "\n"
                + "</body>" + "\n"
            + "</html>";

    return html;
}


MainWindow::~MainWindow()
{
    delete ui;
}

