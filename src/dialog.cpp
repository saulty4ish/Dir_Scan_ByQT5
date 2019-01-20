#include "dialog.h"
#include "ui_dialog.h"
#include <QUrl>

#include <QByteArray>

#include <QNetworkRequest>

#include <QNetworkReply>

#include <iostream>
#include <QTextCodec>
#include <QString>
#include<QDebug>
#include<QProcess>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->textBrowser->setStyleSheet("QTextBrowser{border-width:0;border-style:outset;background: #111111;color: #BBBBBB;}");

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    QString url=ui->lineEdit->text();
    QProcess * po = new QProcess(this);
    po->start("cmd",QStringList()<<"/c"<<"cd lib && whois.exe "+url);
    po->waitForStarted();
    po->waitForFinished();
    //QString temp=QString::fromLocal8Bit(po->readAllStandardOutput());
    QByteArray qba = po->readAllStandardOutput();
    QTextCodec* pTextCodec = QTextCodec::codecForName("System");
    QString str = pTextCodec->toUnicode(qba);
    ui->textBrowser->setText(str);
}

void Dialog::on_pushButton_2_clicked()
{
   reject();
}
