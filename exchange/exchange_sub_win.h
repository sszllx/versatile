#ifndef EXCH_SUB_WIN_H
#define EXCH_SUB_WIN_H

#include <QtWidgets>
#include <QProgressDialog>

class ExchangeHelper;

class ProgressDialog : public  QProgressDialog
{
    Q_OBJECT
 public:
    ProgressDialog(const QString &url, QWidget *parent);

 public slots:
    void networkReplyProgress(qint64 bytesRead, qint64 totalBytes);
};

class ExchangeWin : public QWidget
{
    Q_OBJECT

 public:
    ExchangeWin(QWidget *parent = 0);

 private slots:
    void finished(QString content);

 private:
    void init();
    void initUI();

    ExchangeHelper *m_helper;
    QTextEdit *m_usd_editor;
    QTextEdit *m_profit;
};

#endif // EXCH_SUB_WIN_H
