#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QListWidget>
#include <QBrush>
#include <QPixmap>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loggedIn = false;

    m_view = new QWebEngineView(ui->graphicsView);
    m_view->resize (ui->graphicsView->width (), ui->graphicsView->height ());
    m_view->setHtml(getHtml("TVuipQx5zYY"));
    m_view->show();

    connect(ui->btnSearch, SIGNAL (pressed()), this, SLOT (btnSearchPressed()));

    initializeRecommended();

    ui->gridLayout->addLayout(ui->horizontalLayout_4, 0, 0);

    m_transport = new Transport("localhost", 12345, true, this);
    // Should be done when CONNECT button is pressed
//    if (m_transport->connectToHost()) {
//        qDebug() << "Connected to server";
//    } else {
//        qDebug() << "Failed to connect";
//    }

}

void MainWindow::initializeRecommended()
{
    scroll = new QWidget;
    scroll->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    scroll->setLayout(new QVBoxLayout(ui->scrollArea));

    ui->scrollArea->setWidget(scroll);

    QVector urls = {"b7iVk-ylMB0", "H2v1GnDmLHI", "gGSH_0o-D7g",
                   "b7iVk-ylMB0", "H2v1GnDmLHI", "gGSH_0o-D7g",
                   "b7iVk-ylMB0", "H2v1GnDmLHI", "gGSH_0o-D7g",
                   "b7iVk-ylMB0", "H2v1GnDmLHI", "gGSH_0o-D7g",
                   "b7iVk-ylMB0", "H2v1GnDmLHI", "gGSH_0o-D7g",
                   };

    QLayout *layout = scroll->layout();

    QVector<ThumbnailWidget*> widgets;
    for (auto url : urls) {
        ThumbnailWidget *view = new ThumbnailWidget(url, "song", "performer", "genre", ui->scrollArea);

        connect(view, SIGNAL (clicked(QString)), this, SLOT (btnPlayPressed(QString)));

        view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        layout->addWidget(view);
    }
}

void MainWindow::btnPlayPressed(QString url)
{
    m_view->setHtml(getHtml(url));
}

void MainWindow::btnSearchPressed()
{
    if (!loggedIn) {
        LoginDialog *login = new LoginDialog(this);
        connect(login, SIGNAL (acceptLogin(QString)), this, SLOT (notifyServer(QString)));

        login->exec();

        loggedIn = true;
    }
    queryServer();
}

void MainWindow::queryServer() const
{
    QString genre = ui->txtGenre->text();
    QString performer = ui->txtPerformer->text();
    QString song = ui->txtSong->text();

    QString query = song + "::" + performer + "::" + genre + "::" + m_username;

    qDebug() << "About to send query:" << query;

    if (m_transport->writeData(query)) {
        qDebug() << "Write succeeded";
        m_transport->readData();
    } else {
        qDebug() << "Write failed";
    }
}

void MainWindow::notifyServer(QString username)
{
    //TODO should notify server about the username
    m_username = username;

    qDebug() << "should notify server about the username";
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

