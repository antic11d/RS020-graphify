#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QListWidget>
#include <QBrush>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_view = new QWebEngineView(ui->graphicsView);
    m_view->setHtml(getHtml("TVuipQx5zYY"));
    m_view->resize (ui->graphicsView->width (), ui->graphicsView->height ());
    m_view->show();

    connect(ui->btnSearch, SIGNAL (pressed()), this, SLOT (btnSearchPressed()));
//    connect(ui->scrollArea, SIGNAL ())

    initializeRecommended();

//    auto widget = ui->scrollAreaWidgetContents->focusWidget();
//    qDebug() <<widget;



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
    scroll->setLayout(new QVBoxLayout(scroll));

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
        ThumbnailWidget *view = new ThumbnailWidget(url, ui->graphicsView);

        layout->addWidget(view);
    }
}

void MainWindow::btnSearchPressed()
{
    QString genre = ui->txtGenre->text();
    QString performer = ui->txtPerformer->text();
    QString song = ui->txtSong->text();

    QString query = song + "::" + performer + "::" + genre;

    qDebug() << "About to send query:" << query;


    if (m_transport->writeData(query)) {
        qDebug() << "Write succeeded";
        m_transport->readData();
    } else {
        qDebug() << "Write failed";
    }
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

void MainWindow::initializeResources()
{

}
