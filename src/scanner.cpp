#include "scanner.h"
#include<QMutex>
#include<QThread>
#include<QProgressBar>
#include <QGraphicsItem>


scanner::scanner()
{
    this->stopped=0;
}

void scanner::generate(int startport,int endport)
{
    for(int i=startport;i<=endport;++i)
    {
        this->Q.enqueue(i);
    }
}

void scanner::run()
{
       QMutex mutex;
       QMutex text;
       QString ip=this->ip;
       while(!this->Q.empty()){
       QTcpSocket socket(0);
       socket.abort();
       mutex.lock();
       int tmpport =this->Q.dequeue();
       if(this->stopped)
       {
           mutex.unlock();
           this->nowport=tmpport;
           this->quit();
           break;
       }
       socket.connectToHost(ip,tmpport);
       if(socket.waitForConnected(100))
        {
           text.lock();
           QString message=ip+":";
           message+=QString::number(tmpport,10)+"  opened!";
           emit sig3(message);
           text.unlock();
       }
       emit sentnowport(tmpport);
       mutex.unlock();
       }
}
void scanner::stop()
{
    this->stopped=true;
}

