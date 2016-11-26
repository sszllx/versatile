#ifndef HTTPHELPER_H
#define HTTPHELPER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class HttpHelper : public QObject
{
    Q_OBJECT
public:
    explicit HttpHelper(QObject *parent = 0);

signals:

public slots:

private:
    QUrl m_url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
};

#endif // HTTPHELPER_H
