#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QLineEdit>
#include "mypacket.h"

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    MyTcpServer();
    ~MyTcpServer();

    QTcpSocket* socket;
    QTimer* timer;
    int delay = 0;

    int id = 0;
    QString data1 = "";
    QString data2 = "";

    QLineEdit* statusField;

    void startSending();
    void stopSending();



public slots:
    void startServer(int port, int delay);
    void incomingConnection(qintptr socketDescriptor);
    void sendData();
    void socketReady();
    void socketDisconnect();
};

#endif // MYTCPSERVER_H
