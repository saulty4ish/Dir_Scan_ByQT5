#include "mynetmanager.h"

#include <QUrl>

#include <QByteArray>

#include <QNetworkRequest>

#include <QNetworkReply>

#include <iostream>
#include <QTextCodec>
#include <QString>
#include "ui_mainwindow.h"
#include <QTimer>

using namespace std;

MyNetManager::MyNetManager(QNetworkAccessManager *parent) :

    m_pManager(parent){

}

MyNetManager::~MyNetManager(){

}

bool MyNetManager::get(QUrl url){

    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");
    QTimer timer;
    timer.setInterval(1000);  // 设置超时时间 3 秒
    timer.setSingleShot(true);  // 单次触发
    QNetworkReply *reply = m_pManager->head(request);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    connect(&timer,SIGNAL(timeout()),&loop,SLOT(quit()));
    timer.start();
    loop.exec();
    if (timer.isActive()){
        timer.stop();
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    str = codec->toUnicode(reply->readAll());
    //响应码
    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if(code==200||code==403||code==301||code==302)
    {
        reply->deleteLater();
         return true;
    }
    else{
        reply->deleteLater();
        return false;
    }
    }
    else
    {
        reply->abort();
        return false;
    }

}

QString MyNetManager::get1(QUrl url){
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");
    QTimer timer;
    timer.setInterval(1000);  // 设置超时时间 3 秒
    timer.setSingleShot(true);  // 单次触发
    QNetworkReply *reply = m_pManager->get(request);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    connect(&timer,SIGNAL(timeout()),&loop,SLOT(quit()));
    timer.start();
    loop.exec();
    if (timer.isActive()){
        timer.stop();
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    str = codec->toUnicode(reply->readAll());
    reply->deleteLater();
    return str;
}
    else{
        reply->abort();
        return QString("false");
    }
}
bool MyNetManager::post(QUrl url, QByteArray &bytes){

    QNetworkRequest request;

    request.setUrl(url);

    QNetworkReply *reply = m_pManager->post(request,bytes);

    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),

            this,SLOT(downloadProgress(qint64,qint64)));

    return true;

}

void MyNetManager::slot_replayFinished(){

}
