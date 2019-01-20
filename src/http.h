#ifndef HTTP_H

#define HTTP_H

#include <QObject>

#include <QNetworkAccessManager>

class MyNetManager : public QObject

{

    Q_OBJECT

public:

    explicit MyNetManager(QNetworkAccessManager *pManager);

    ~MyNetManager();

    bool get(QUrl url);

    bool post(QUrl url,QByteArray& bytes);

signals:

public slots:

    void downloadProgress(qint64 bytesSent, qint64 bytesTotal);

    void finished();

private:

    QNetworkAccessManager *m_pManager;

};

#endif
