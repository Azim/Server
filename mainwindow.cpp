#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpServer.statusField = ui->tcpStatusLineEdit;

    //QCoreApplication::setOrganizationName("Azim");
    //QCoreApplication::setOrganizationDomain("azim.icu");
    //QCoreApplication::setApplicationName("Server");
}

MainWindow::~MainWindow()
{
    settings->sync();
    delete ui;
}

void MainWindow::loadSettings(){
    //tcp
    ui->tcpPortLineEdit->setText(settings->value("tcp/port", "").toString());
    ui->tcpDelayLineEdit->setText(settings->value("tcp/delay", "").toString());
    ui->tcpDataLineEdit->setText(settings->value("tcp/data", "").toString());
    ui->tcpData2LineEdit->setText(settings->value("tcp/data2", "").toString());
    //udp
    ui->udpIpLineEdit->setText(settings->value("udp/ip","").toString());
    ui->udpPortLineEdit->setText(settings->value("udp/port","").toString());
    ui->udpDelayLineEdit->setText(settings->value("udp/delay","").toString());
    ui->udpDataLineEdit->setText(settings->value("udp/data","").toString());
    ui->udpData2LineEdit->setText(settings->value("udp/data2","").toString());
}

void MainWindow::on_tcpStartButton_clicked()
{
    settings->setValue("tcp/port", ui->tcpPortLineEdit->text());
    settings->setValue("tcp/delay", ui->tcpDelayLineEdit->text());

    tcpServer.startServer(ui->tcpPortLineEdit->text().toInt(), ui->tcpDelayLineEdit->text().toInt());
    qDebug()<<"Started TCP server";
    ui->tcpStatusLineEdit->setText("Waiting for client");
}


void MainWindow::on_tcpStopButton_clicked()
{
    tcpServer.stopSending();
    if(tcpServer.isListening()){
        tcpServer.close();
        qDebug()<<"Stopped TCP server";
        ui->tcpStatusLineEdit->setText("Offline");
    }else{
        qDebug()<<"Server wasn't running";
    }
}

void MainWindow::on_udpStartButton_clicked()
{
    settings->setValue("udp/ip", ui->udpIpLineEdit->text());
    settings->setValue("udp/port", ui->udpPortLineEdit->text());
    settings->setValue("udp/delay", ui->udpDelayLineEdit->text());

    udpServer.data1 = ui->udpDataLineEdit->text();
    udpServer.data2 = ui->udpData2LineEdit->text();
    udpServer.startRepeatingSend(ui->udpIpLineEdit->text(),ui->udpPortLineEdit->text().toInt(),ui->udpDelayLineEdit->text().toInt());
    qDebug()<<"Started sending UDP packets";
    ui->udpStatusLineEdit->setText("Sending UDP packets");
}


void MainWindow::on_udpStopButton_clicked()
{
    udpServer.stopRepeatingSend();
    qDebug()<<"Stopped sending UDP packets";
    ui->udpStatusLineEdit->setText("Offline");
}

void MainWindow::on_tcpDataLineEdit_editingFinished()
{
    settings->setValue("tcp/data", ui->tcpDataLineEdit->text());
    tcpServer.data1 = ui->tcpDataLineEdit->text();
}


void MainWindow::on_tcpData2LineEdit_editingFinished()
{
    settings->setValue("tcp/data2", ui->tcpData2LineEdit->text());
    tcpServer.data2 = ui->tcpData2LineEdit->text();
}


void MainWindow::on_udpDataLineEdit_editingFinished()
{
    settings->setValue("udp/data", ui->udpDataLineEdit->text());
    udpServer.data1 = ui->udpDataLineEdit->text();
}


void MainWindow::on_udpData2LineEdit_editingFinished()
{
    settings->setValue("udp/data2", ui->udpData2LineEdit->text());
    udpServer.data2 = ui->udpData2LineEdit->text();
}

