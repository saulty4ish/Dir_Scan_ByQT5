#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include "nithread.h"
#include <QProgressBar>
#include "portscan.h"
#include <QQueue>
#include <synchapi.h>
#include <QCoreApplication>
#include <QUrl>
#include<QMessageBox>
#include <QDragEnterEvent>
#include <QMimeData>
#include<QDir>
#include<QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QQueue <QString> url;
    bool isfile=0;
    void combo_box();
    QStringList string_list;
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_actionwhois_triggered();

    void on_actionsubdomain_triggered();
    void lot(QString url);
    void lot1(QString url);
    void on_actionPort_Scan_triggered();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    Ui::MainWindow *ui;
    Dialog *new_win;
    portscan * port;
    nithread *threadd;
    QProgressBar *pProgressBar;
    bool twice=0;
};

#endif // MAINWINDOW_H
