#include "myudpserver.h"

MyUdpServer::MyUdpServer()
{
    socket = new QUdpSocket(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(sendData()));
}
MyUdpServer::~MyUdpServer()
{
    timer->deleteLater();
    socket->deleteLater();
}

void MyUdpServer::startRepeatingSend(QString adress, int port, int delay){
    this->adress = adress;
    this->port = port;
    timer->start(delay);
    qDebug()<<"Started timer";
}

void MyUdpServer::stopRepeatingSend(){
    timer->stop();
    qDebug()<<"Stopped timer";
}

void MyUdpServer::sendData(){
    MyPacket packet {id++, data1, data2};
    if(socket->writeDatagram(packet, QHostAddress(adress), port) == -1){
        qDebug()<<"Error occured while sending packet";
    }else{
        qDebug()<<"Sent packet";
    }
}
