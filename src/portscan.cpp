#include "portscan.h"
#include "ui_portscan.h"


portscan::portscan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::portscan)
{
    ui->setupUi(this);
    ui->textBrowser->setStyleSheet("QTextBrowser{border-width:0;border-style:outset;background: #111111;color: #BBBBBB;}");
    scan=new scanner();
    setAcceptDrops(true);
    connect(scan,SIGNAL(sentnowport(int)),this,SLOT(setBar(int)));
    connect(scan, SIGNAL(sig3(QString)), this, SLOT(lot(QString)));
}

portscan::~portscan()
{
    delete ui;
}

void portscan::setBar(int value)
{
    qDebug()<<value;
    ui->progressBar->setValue(value);
    QString str=QString("正在扫描： %1").arg(scan->ip);
    ui->label_4->setText(QString(str+":%1").arg(value));
}

void portscan::lot(QString message)
{
    ui->textBrowser->append(message);
}

bool portscan::checkip(QString ip)
{
    QRegExp rx2("\\d+\\.\\d+\\.\\d+\\.\\d+");
     if( !rx2.exactMatch(ip) )
     {
           return false;
     }
     //qDebug()<<"check true";
     return true;
}


void portscan::on_pushButton_clicked()
{
    QString desip=ui->lineEdit->text();
    ui->progressBar->setValue(0);
    if(this->isfile){
        ui->spinBox->setValue(scan->nowport);
        staport=ui->spinBox->value();
        endport=ui->spinBox_2->value();
        ui->progressBar->setRange(staport,endport);
        scan->stopped=0;
        int num=ui->lineEdit_2->text().toInt();
        while(!this->url.empty()){
            scan->generate(staport,endport);
            scan->ip=this->url.dequeue();
        }
        for(int i=0;i<num;i++)
        {
            scan->start();
        }
    }
    else{
    if(!checkip(desip))
        {
            ui->lineEdit->setText("ip 地址错误");
        }
        else
        {
             ui->spinBox->setValue(scan->nowport);
             ip=desip;
             staport=ui->spinBox->value();
             endport=ui->spinBox_2->value();
             ui->progressBar->setRange(staport,endport);
             scan->generate(staport,endport);
             scan->ip=ip;
             scan->stopped=0;
             int num=ui->lineEdit_2->text().toInt();
             for(int i=0;i<num;i++)
             {
                 scan->start();
             }
        }
    }
}

void portscan::on_pushButton_2_clicked()
{
     scan->stopped=1;
}

void portscan::dragEnterEvent(QDragEnterEvent *event)
{
    //如果为文件，则支持拖放
   // if (event->mimeData()->hasFormat("text/uri-list"))
   event->acceptProposedAction();
}

void portscan::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    this->isfile=1;
    if(urls.isEmpty())
        return;
    //往文本框中追加文件名
    foreach(QUrl url, urls) {
        QString file_name = url.toLocalFile();
        ui->lineEdit->setText(file_name);
        QFile file(file_name);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            while(!file.atEnd()){
            QByteArray ba = file.readLine();
            QString str(ba);
            str=str.remove(QChar('\n'), Qt::CaseInsensitive);
            this->url.enqueue(str);
        }
        file.close();
      }
    }
}
