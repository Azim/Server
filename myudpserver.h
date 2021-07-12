#ifndef MYUDPSERVER_H
#define MYUDPSERVER_H

#include <QUdpSocket>
#include "mypacket.h"
#include <QTimer>


class MyUdpServer:QObject
{
    Q_OBJECT
public:
    MyUdpServer();
    ~MyUdpServer();

    QUdpSocket* socket;
    QTimer* timer;
    int port;
    QString adress;

    int id = 0;
    QString data1 = "";
    QString data2 = "";

    void startRepeatingSend(QString adress, int port, int delay);
    void stopRepeatingSend();


public slots:
    void sendData();
};

#endif // MYUDPSERVER_H
