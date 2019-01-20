#include "proxy.h"
#include <QNetworkProxy>
#include <QFile>
#include <QtGlobal>
#include <QTime>
proxy::proxy()
{
    this->proxy1.setType(QNetworkProxy::Socks5Proxy);
}

QNetworkProxy proxy::setproxy()
{
    int size=this->container.size();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int index =qrand()%(size-1);
    QString proxy=this->container[index];
    QString url=proxy.split(":")[0];
    int port=proxy.split(":")[1].toInt();
    qDebug()<<url;
    qDebug()<<port;
    this->proxy1.setType(QNetworkProxy::HttpProxy);
    this->proxy1.setHostName(url);
    this->proxy1.setPort(port);
    /*this->proxy1.setHostName("127.0.0.1");
    this->proxy1.setPort(8080);*/
    return this->proxy1;
}

void proxy::generatelist(){
QFile file("./config/proxy/proxy");
if(file.open(QIODevice::ReadOnly | QIODevice::Text))
{
    while(!file.atEnd()){
    QByteArray ba = file.readLine();
    QString str(ba);
    this->container.append(str.remove(QChar('\n')));
 }
    file.close();
}
}
