#ifndef PROXY_H
#define PROXY_H
#include<QNetworkProxy>

class proxy
{
public:
    QNetworkProxy  proxy1;
    proxy();
    QNetworkProxy setproxy();
    void generatelist();
    QStringList container;
};

#endif // PROXY_H
