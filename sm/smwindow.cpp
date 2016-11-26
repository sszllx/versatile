#include "smwindow.h"
#include "smproject.h"
#include "smobj.h"
#include "../qjsonmodel.h"

#include <QtWidgets>
#include <QUuid>
#include <QWebEngineView>

using namespace SM;

SMWindow::SMWindow(QWidget *parent)
    : QMdiSubWindow(parent, Qt::Window)
{
    setWindowTitle("sm");

    //    mCurrentProject.reset(new SMProject);

    initUI();
}

void SMWindow::initUI()
{
    QWidget *main_widget = new QWidget(this);
    setWidget(main_widget);
    QVBoxLayout *main_layout = new QVBoxLayout(main_widget);

    QSplitter *content_splitter = new QSplitter(this);
    content_splitter->setOrientation(Qt::Horizontal);

    mJsonModel = new QJsonModel(this);
    mTreeview = new QTreeView(main_widget);
    mTreeview->setModel(mJsonModel);
    mWebEngineView = new QWebEngineView(main_widget);
    content_splitter->addWidget(mTreeview);
    content_splitter->addWidget(mWebEngineView);

    QHBoxLayout *btn_layout = new QHBoxLayout(main_widget);
    QPushButton *qa_btn = new QPushButton("Insert Q&A");
    btn_layout->addWidget(qa_btn);

    mUrlEditor = new QLineEdit(main_widget);
    connect(mUrlEditor, &QLineEdit::returnPressed, this, &SMWindow::onLoadUrl);
    btn_layout->addWidget(mUrlEditor);

    main_layout->addWidget(content_splitter);
    main_layout->addLayout(btn_layout);

#if 1
    QFile file("./test/test.json");
    file.open(QIODevice::ReadOnly);
    QTextStream out(&file);
    QString data = out.readAll();
    mJsonModel->loadJson(data.toLocal8Bit());
#endif
}

void SMWindow::onAddItem()
{

}

void SMWindow::onAddQA()
{

}

void SMWindow::onLoadUrl()
{
    QString url = mUrlEditor->text();
    if (!url.startsWith("http")) {
        url.prepend("http://");
    }

    qDebug() << "url: " << url;

    mWebEngineView->load(QUrl(url));
}

void SMWindow::addTopic()
{
    if (mWebEngineView == NULL) {
        return;
    }

    QString selectText = mWebEngineView->selectedText();

    if (selectText.isEmpty()) {
        return;
    }

    qDebug() << selectText;

    if (mCurrentProject.isNull()) {
        // add root object
        mCurrentProject.reset(new SMProject);

        QSharedPointer<sm_obj_t> obj = SM::newSMObj();
        obj->uuid = QUuid::createUuid().toString();
        qDebug() << "uuid:  " << obj->uuid;
        obj->obj_type = SM::topic;
        sm_item_t item;
        item.type = SM::string;
        item.uri = selectText;
        obj->questions.append(item);

        mCurrentProject->addRootObj(obj);

        return;
    }

}

void SMWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << event->key();
    qDebug() << event->modifiers();

    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_T) {
        // press t
        // add topic
        addTopic();
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_L) {
        // ctrl + l
        mUrlEditor->setFocus();
    }

    QMdiSubWindow::keyPressEvent(event);
}
