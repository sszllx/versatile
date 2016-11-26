#include <QtWidgets>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "httphelper.h"
#include "mdichild.h"
#include "exchange/exchange_sub_win.h"
#include "sm/smwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mHttpHelper (new HttpHelper(this)),
    mdiArea(new QMdiArea)
{
    ui->setupUi(this);

    setWindowTitle(tr("Versatile"));

    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    connect(mdiArea, &QMdiArea::subWindowActivated,
            this, &MainWindow::updateMenus);

    createActions();

    setGeometry(10, 800, 800, 800);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    mdiArea->closeAllSubWindows();
    if (mdiArea->currentSubWindow()) {
        event->ignore();
    }
}

void MainWindow::updateMenus()
{

}

void MainWindow::updateVerMenu()
{
    mVerMenu->addAction(mExchangeAct);
    mVerMenu->addAction(mSMAct);
}

void MainWindow::onNewExchange()
{
    ExchangeWin *ew = new ExchangeWin;

    mdiArea->addSubWindow(ew);
    ew->showMaximized();
}

void MainWindow::onSM()
{
    // for test
    SMWindow *sw = new SMWindow(this);

    mdiArea->addSubWindow(sw);
    sw->showMaximized();
}

void MainWindow::newFile()
{
    MdiChild *child = createMdiChild();
    child->show();
}

MdiChild* MainWindow::createMdiChild()
{
    MdiChild *child = new MdiChild;
    mdiArea->addSubWindow(child);

    return child;
}

// not use
void MainWindow::onPullTopic()
{
    QMdiSubWindow *activeWin = mdiArea->activeSubWindow();
    QString title = activeWin->windowTitle();

    if (title != "sm") {
        return;
    }

    SMWindow *smwin = static_cast<SMWindow *>(activeWin);
    smwin->addTopic();
}

void MainWindow::createActions()
{
    mVerMenu = menuBar()->addMenu(tr("&Versatile"));
    connect(mVerMenu, &QMenu::aboutToShow, this, &MainWindow::updateVerMenu);

    mExchangeAct = new QAction(QIcon(), tr("&exchange"), this);
    connect(mExchangeAct, &QAction::triggered, this, &MainWindow::onNewExchange);

    mSMAct = new QAction(QIcon(), tr("&Sm"), this);
    connect(mSMAct, &QAction::triggered, this, &MainWindow::onSM);

    mPullTopicAct = new QAction(QIcon(), tr("&Topic"), this);
    connect(mPullTopicAct, &QAction::triggered, this, &MainWindow::onPullTopic);

    mToolBar = addToolBar(tr("exchange"));
    mToolBar->addAction(mExchangeAct);
    mToolBar->addAction(mSMAct);
    mToolBar->addAction(mPullTopicAct);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}
