#include "mytcpserver.h"

MyTcpServer::MyTcpServer()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(sendData()));
}

MyTcpServer::~MyTcpServer(){
    socket->deleteLater();
    timer->deleteLater();
}

void MyTcpServer::startServer(int port, int delay)
{
    this->delay = delay;
    if (this->listen(QHostAddress::Any, port))
    {
        qDebug()<<"Server listening on port "<<port;
        statusField->setText("Waiting for client");
    }
    else
    {
        qDebug()<<"Error while trying to listen on port "<<port;
        statusField->setText("Unable to start listening");
    }
}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket,SIGNAL(readyRead()),this,SLOT(socketReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(socketDisconnect()));

    qDebug()<<"Client connected: "<<socketDescriptor;
    qDebug()<<"Sending packets now";
    statusField->setText("Client connected");
    startSending();
}

void MyTcpServer::startSending(){
    timer->start(delay);
    statusField->setText("Sending packets");
}
void MyTcpServer::stopSending(){
    timer->stop();
    statusField->setText("Offline");
}

void MyTcpServer::sendData(){
    MyPacket data (id++, this->data1, this->data2);
    socket->write(data);
}

void MyTcpServer::socketReady()
{
    if (socket->waitForConnected(500))
    {
        socket->waitForReadyRead(500);
        QByteArray msg = socket->readAll();
        qDebug()<<"Recieved data from client: "<<msg;
    }
}

void MyTcpServer::socketDisconnect()
{
    stopSending();
    qDebug()<<"Client disconnected";
    statusField->setText("Waiting for client");
    socket->deleteLater();
}
