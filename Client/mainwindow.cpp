#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <QDebug>
#include <QMessageBox>
#include <QListWidget>
#include "sockabstract.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->userName->hide();
    ui->login->hide();
    ui->groups->hide();
    sockAbstract sock;
    sock.init();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_start_clicked()
{
    ui->userName->show();
    ui->login->show();
    ui->start->hide();
}

void MainWindow::on_login_clicked()
{
    /*tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connectSuc()));
    tcpSocket->abort();
    tcpSocket->connectToHost("120.26.77.201",
                             4000);
                             */
    connect(socket.tcpSocket, SIGNAL(connected()), &socket, SLOT(connectSuc()));
    socket.init();
    ui->login->setDisabled(true);



}


void MainWindow::connectSuc()
{

    qDebug()<<"connected"<<endl;
    ui->login->hide();
    ui->userName->hide();

    for(int i = 1; i < 9; i++)
    {
        ui->groups->addItem("group " + QString::number(i) + " 目前人数：" + QString::number(rand()%3));
    }
    ui->groups->show();
}
