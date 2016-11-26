#include "exchange_helper.h"

#include <QtNetwork>
#include <QDebug>

ExchangeHelper::ExchangeHelper(QObject *parent)
    : QObject(parent)
{

}

void ExchangeHelper::request(const QUrl &url)
{
    reply = qnam.get(QNetworkRequest(url));

    // connect(reply, &QNetworkReply::finished, this, &ExchangeHelper::finished);
    connect(reply, &QNetworkReply::finished, this, &ExchangeHelper::onHttpFinished);
    connect(reply, &QIODevice::readyRead, this, &ExchangeHelper::onHttpReadyRead);
    connect(reply, &QNetworkReply::downloadProgress, this, &ExchangeHelper::downloadProgress);
}

void ExchangeHelper::onHttpFinished()
{
    qDebug() << __FUNCTION__;
    QUrl url;
    const QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    reply->deleteLater();
    reply = Q_NULLPTR;
    if (!redirectionTarget.isNull()) {
        const QUrl redirectedUrl = url.resolved(redirectionTarget.toUrl());
        request(redirectedUrl);
    }


    emit finished(mContent);
}

void ExchangeHelper::onHttpReadyRead()
{
    QString content = reply->readAll();
    mContent.append(content);
}

void ExchangeHelper::onCancelDownload()
{
    qDebug() << __FUNCTION__;
    reply->abort();
}

