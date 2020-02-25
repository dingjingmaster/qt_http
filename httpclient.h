#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QJsonObject>
#include <QNetworkAccessManager>


class HTTPClient
{
public:
    HTTPClient();
    HTTPClient(QString url);
    ~HTTPClient();

    void postJSON(QJsonObject& js);
    void setURL(QString url);

private:
    QUrl* mRequestURL;
    QNetworkAccessManager* mNetworkManager;
};

#endif // HTTPCLIENT_H
