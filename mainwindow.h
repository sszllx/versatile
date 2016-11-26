#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class HttpHelper;
class QAction;
class QMenu;
class QMdiArea;
class QMdiSubWindow;
class QToolBar;
class MdiChild;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event);

private slots:
    void updateMenus();
    void updateVerMenu();
    void newFile();
    void onNewExchange();
    void onSM();
    void onPullTopic();

    MdiChild* createMdiChild();

private:
    void createActions();

    Ui::MainWindow *ui;

    HttpHelper *mHttpHelper;
    QMdiArea *mdiArea;

    QMenu *mVerMenu;
    QToolBar *mToolBar;
    QAction *mExchangeAct;
    QAction *mSMAct;
    QAction *mPullTopicAct;
};

#endif // MAINWINDOW_H
