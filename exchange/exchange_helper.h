#ifndef EXCHANGE_HELPER_H
#define EXCHANGE_HELPER_H

#include <QtCore>
#include <QNetworkAccessManager>
#include <QUrl>

class QNetworkReply;

class ExchangeHelper : public QObject
{
    Q_OBJECT
 public:
    ExchangeHelper(QObject *parent = NULL);

    void request(const QUrl& url);

 public slots:
    void onCancelDownload();

 private slots:
    void onHttpFinished();
    void onHttpReadyRead();

 signals:
    void downloadProgress(qint64 bytesRead, qint64 botalBytes);
    void finished(QString content);

 private:
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QString mContent;
};


#endif // EXCHANGE_HELPER_H
