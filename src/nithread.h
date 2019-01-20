//自定义线程类,头文件
#ifndef NITHREAD_H
#define NITHREAD_H

#include <QThread>
#include <QQueue>
#include "mynetmanager.h"
#include <qfile.h>
#include <QElapsedTimer>
#include "proxy.h"

class nithread : public QThread
{
    Q_OBJECT
public:
    explicit nithread(QObject *parent = 0);
    QQueue <QString> Q;
    int Total;
    QString base;
    void GenerateTasks(QString Type);
    bool isstop=0;
    bool isproxy=0;
    int time=0;
signals:
    void sig(QString url);
    void sig1(QString url);

protected:
    void run();

public slots:
};

#endif // NITHREAD_H
