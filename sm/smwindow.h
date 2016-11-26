#ifndef SMWINDOW_H
#define SMWINDOW_H

#include <QtWidgets>
#include <QSharedPointer>

class QWebEngineView;
class SMProject;
class QJsonModel;

class SMWindow : public QMdiSubWindow
{
 public:
    SMWindow(QWidget *parent = NULL);

    void addTopic();

 public slots:
    void onAddItem();
    void onAddQA();
    void onLoadUrl();

 protected:
    void keyPressEvent(QKeyEvent *event);

 private:
    void initUI();

    QLineEdit *mUrlEditor;
    QWebEngineView *mWebEngineView;
    QSharedPointer<SMProject> mCurrentProject;

    QTreeView *mTreeview;
    QJsonModel *mJsonModel;
};

#endif // SMWINDOW_H
