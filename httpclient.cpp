#include "httpclient.h"

#include <QEventLoop>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QTextCodec>

HTTPClient::HTTPClient()
{
    this->mRequestURL = new QUrl();
    this->mNetworkManager = new QNetworkAccessManager();
}

HTTPClient::HTTPClient(QString url)
{
    this->mRequestURL = new QUrl();
    this->mNetworkManager = new QNetworkAccessManager();

    this->setURL(url);
}

HTTPClient::~HTTPClient()
{
    delete this->mRequestURL;
    delete this->mNetworkManager;
}

void HTTPClient::postJSON(QJsonObject& js)
{
    QNetworkReply* ret = NULL;
    QNetworkRequest request;
//    QTextCodec *codec = QTextCodec::codecForName("utf8");
    request.setUrl(QUrl("http://127.0.0.1:6000"));

    // multipart/form-data
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QJsonDocument(js).toJson().length());

    ret = this->mNetworkManager->post(request, QJsonDocument(js).toJson());

    QEventLoop eventLoop;
    QObject::connect(mNetworkManager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    ret->waitForReadyRead(1000);
    QByteArray bytes = ret->readAll();
    qDebug() << bytes;
    ret->close();
}

void HTTPClient::setURL(QString url)
{
    if (url.isNull() || url.isEmpty())
        return;
    this->mRequestURL->setUrl(url);
    this->mRequestURL->setPort(6000);
}
