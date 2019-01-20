#include "http.h"

#include <QUrl>

#include <QByteArray>

#include <QNetworkRequest>

#include <QNetworkReply>

#include <iostream>

using namespace std;

MyNetManager::MyNetManager(QNetworkAccessManager *parent) :

    m_pManager(parent){

}

MyNetManager::~MyNetManager(){

}

bool MyNetManager::get(QUrl url){

    QNetworkRequest request;

    request.setUrl(url);

    QNetworkReply *reply = m_pManager->get(request);

    connect(reply,SIGNAL(finished()),this,SLOT(finished()));

    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),

            this,SLOT(downloadProgress(qint64,qint64)));

    return true;

}

bool MyNetManager::post(QUrl url, QByteArray &bytes){

    QNetworkRequest request;

    request.setUrl(url);

    QNetworkReply *reply = m_pManager->post(request,bytes);

    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),

            this,SLOT(downloadProgress(qint64,qint64)));

    return true;

}

void MyNetManager::finished(){

    QNetworkReply* reply = (QNetworkReply*)sender();

    reply->deleteLater();

}

void MyNetManager::downloadProgress(qint64 bytesSent, qint64 bytesTotal){

    cout<< "\ndownloadProgress done:\n";

    cout << "bytesSent: " << bytesSent

         << "  " << "bytesTocal: " << bytesTotal;

}
