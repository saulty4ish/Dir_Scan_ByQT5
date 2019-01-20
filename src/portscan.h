#ifndef PORTSCAN_H
#define PORTSCAN_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QTcpSocket>
#include "scanner.h"
#include <QQueue>
#include <QDragEnterEvent>
#include <QMimeData>

namespace Ui {
class portscan;
}

class portscan : public QDialog
{
    Q_OBJECT

public:
    explicit portscan(QWidget *parent = 0);
    bool checkip(QString ip);
    void startscanner(QString ip,int startport,int endport);
    QQueue <QString> url;
    bool isfile=0;
    ~portscan();

private slots:
    void on_pushButton_clicked();
    void setBar(int value);
    void lot(QString url);
    void on_pushButton_2_clicked();
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    Ui::portscan *ui;
    scanner * scan;
    int nowport;
    int staport;
    int endport;
    int num;
    QString ip;
};

#endif // PORTSCAN_H
