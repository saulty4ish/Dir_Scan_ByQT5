#ifndef MYNETMANAGER_H

#define MYNETMANAGER_H

#include <QObject>

#include <QNetworkAccessManager>

class MyNetManager : public QObject

{

    Q_OBJECT
public:
    explicit MyNetManager(QNetworkAccessManager *pManager);
    ~MyNetManager();
    QString str="";

    bool get(QUrl url);
    QString get1(QUrl url);

    bool post(QUrl url,QByteArray& bytes);



signals:

private Q_SLOTS:
    void slot_replayFinished();

private:

    QNetworkAccessManager *m_pManager;

};

#endif // MYNETMANAGER_H
