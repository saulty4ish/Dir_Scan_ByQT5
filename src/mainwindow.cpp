#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mynetmanager.h"
#include "dialog.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textBrowser->setStyleSheet("QTextBrowser{border-width:0;border-style:outset;background: #111111;color: #BBBBBB;}");
    QFile file(":/qss/test1.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);
    file.close();
    combo_box();
    threadd = new nithread(this);
    connect(threadd, SIGNAL(sig(QString)), this, SLOT(lot(QString)));
    connect(threadd, SIGNAL(sig1(QString)), this, SLOT(lot1(QString)));
    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::combo_box()
{
    QDir dir("./config/exts");
        if(!dir.exists())
            return;
    int dir_count = dir.count();
    if(dir_count <= 0)
      {return;}
    ui->comboBox->addItem("NULL");
    for(int i=0; i<dir_count; i++)
       {
        QString file_name = dir[i];  //文件名称

        if(file_name!="." && file_name!=".."){
        ui->comboBox->addItem(file_name);
        this->string_list.append(file_name);
        }
       }
}
void MainWindow::lot(QString url)
{
    ui->textBrowser->append(url);
}

void MainWindow::lot1(QString url)
{
    int progess=(1.0-(float(threadd->Q.size())/float(threadd->Total)))*100;
    ui->progressBar->setValue(progess);
    ui->label_4->setText(QString("%1").arg(url));
}


void MainWindow::on_pushButton_clicked()
{
 if(this->twice==0){
    if(this->isfile){
        while(!this->url.empty())
        {
        QString str=this->url.dequeue();
        threadd->base=str;
        if(ui->checkBox->checkState()){
            threadd->GenerateTasks("./config/php");
        };
        if(ui->checkBox_2->checkState()){
            threadd->GenerateTasks("./config/asp");
        };
        if(ui->checkBox_3->checkState()){
            threadd->GenerateTasks("./config/aspx");
        };
        if(ui->checkBox_4->checkState()){
            threadd->GenerateTasks("./config/java");
        };
        if(ui->checkBox_5->checkState()){
            threadd->GenerateTasks("./config/dir");
        };
        if(ui->checkBox_7->checkState()){
            threadd->GenerateTasks("./config/backup");
        };
        if(ui->checkBox_6->checkState()){
            threadd->GenerateTasks("./config/ctf");
        };
        if(ui->comboBox->currentText()!="")
        {
            for(int i=0;i<this->string_list.size();++i)
            {
                if(ui->comboBox->currentText()==this->string_list[i])
                {
                    threadd->GenerateTasks("./config/exts/"+ui->comboBox->currentText());
                }
            }
        };
        }
        if(ui->checkBox_9->checkState()){
            threadd->isproxy=1;
        };
        int threadnum=ui->lineEdit_2->text().toInt();
        if(ui->checkBox_8->checkState()){
            threadd->time=3000;
            threadd->start();
        }
        else{
        for(int i=0;i<threadnum;++i){
        threadd->start();
        }
        }
    }
else{
    QString base=ui->lineEdit->text();
    threadd->base=base;
    QRegExp rx("http[s]*://\\S+/");
    QRegExpValidator v(rx, 0);
    int pos=0;
    int threadnum=ui->lineEdit_2->text().toInt();
    if(v.validate(base, pos)==0 || base=="")
    {
        QMessageBox::warning(NULL, "输入错误", "您输入的url有误，请重新输入.", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    if(ui->checkBox->checkState()){
        threadd->GenerateTasks("./config/php");
    };
    if(ui->checkBox_2->checkState()){
        threadd->GenerateTasks("./config/asp");
    };
    if(ui->checkBox_3->checkState()){
        threadd->GenerateTasks("./config/aspx");
    };
    if(ui->checkBox_4->checkState()){
        threadd->GenerateTasks("./config/java");
    };
    if(ui->checkBox_5->checkState()){
        threadd->GenerateTasks("./config/dir");
    };
    if(ui->checkBox_7->checkState()){
        threadd->GenerateTasks("./config/backup");
    };
    if(ui->checkBox_6->checkState()){
        threadd->GenerateTasks("./config/ctf");
    };
    if(ui->comboBox->currentText()!="")
    {
        for(int i=0;i<this->string_list.size();++i)
        {
            if(ui->comboBox->currentText()==this->string_list[i])
            {
                threadd->GenerateTasks("./config/exts/"+ui->comboBox->currentText());
            }
        }
    };
    if(ui->checkBox_9->checkState()){
        threadd->isproxy=1;
    };
    if(ui->checkBox_8->checkState()){
        threadd->time=3000;
        threadd->start();
    }
    else
    {
    for(int i=0;i<threadnum;++i){
    threadd->start();
    }
    }
        }
    this->twice=1;
    threadd->isstop=0;
    ui->pushButton->setText("停止");
    }
    else{
        threadd->isstop=1;
        ui->pushButton->setText("开始");
        this->twice=0;
    }
    }

void MainWindow::on_actionwhois_triggered()
{
    new_win = new Dialog(this);
    new_win->setModal(false);
    new_win->show();
}
void MainWindow::on_actionsubdomain_triggered()
{

}

void MainWindow::on_actionPort_Scan_triggered()
{
    port = new portscan(this);
    port->setModal(false);
    port->show();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    //如果为文件，则支持拖放
   // if (event->mimeData()->hasFormat("text/uri-list"))
   event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    this->isfile=1;
    if(urls.isEmpty())
        return;
    //往文本框中追加文件名
    foreach(QUrl url, urls) {
        QString file_name = url.toLocalFile();
        ui->lineEdit_3->setText(file_name);
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
