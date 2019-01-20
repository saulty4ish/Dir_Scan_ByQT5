#ifndef SCANNER_H
#define SCANNER_H
#include<QThread>
#include<QTcpSocket>
#include <QQueue>


class scanner:public QThread
{
    Q_OBJECT
public:
    scanner();
    void run();//不多说，自己Google
    void stop();//实现线程安全停止，用Terminate是不安全的
    void generate(int startport,int endport);
    QQueue <int> Q;
    QString ip;
    bool stopped=0;
    int nowport=0;

signals:
    void sentnowport(int value);
    void sig3(QString url);

};

#endif // SCANNER_H
