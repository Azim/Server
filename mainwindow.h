#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

#include "mytcpserver.h"
#include "myudpserver.h"
#include "mypacket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadSettings();


    QSettings* settings;

private slots:
    void on_tcpStartButton_clicked();

    void on_tcpStopButton_clicked();

    void on_udpStartButton_clicked();

    void on_udpStopButton_clicked();

    void on_tcpDataLineEdit_editingFinished();

    void on_tcpData2LineEdit_editingFinished();

    void on_udpDataLineEdit_editingFinished();

    void on_udpData2LineEdit_editingFinished();

private:
    Ui::MainWindow *ui;
    MyTcpServer tcpServer;
    MyUdpServer udpServer;
};
#endif // MAINWINDOW_H
