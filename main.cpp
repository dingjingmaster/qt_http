#include "httpclient.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QJsonObject js;
    js.insert("a", "1");

    HTTPClient client("127.0.0.1");
    client.postJSON(js);

    return a.exec();
}
