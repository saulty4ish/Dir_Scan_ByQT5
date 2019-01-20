//自定义线程类cpp
#include "nithread.h"
#include <QMutex>
nithread::nithread(QObject *parent) : QThread(parent)
{
}

void nithread::GenerateTasks(QString Type)
{
    QFile file(Type);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd()){
        QByteArray ba = file.readLine();
        QString str(ba);
        str=this->base+str;
        this->Q.enqueue(str.remove(QChar('\n'), Qt::CaseInsensitive));
        }
        this->Total=Q.size();
        file.close();
  }
}

void nithread::run()
{
        QMutex mutex;
        int status=0;
        QString url="";
        QNetworkAccessManager *netManager =new QNetworkAccessManager();
        MyNetManager manager(netManager);
        while(!this->Q.empty()){
        if(this->isstop)
        {
            this->quit();
            break;
        }
        mutex.lock();
        url=this->Q.dequeue();
        qDebug()<<QString(url);
        if(this->isproxy){
            proxy * test=new proxy();
            test->generatelist();
            test->setproxy();
            netManager->setProxy(test->proxy1);
        }
        status=manager.get(QUrl(url));
        if(this->time)
        {
           msleep(3000);
        }
        emit sig1(url);
        mutex.unlock();
        if(status){
        emit sig(url);
        }
        }
        msleep(100);
}
