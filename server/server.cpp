#include "server.h"

#include <QDataStream>

#define ENQ "\x05"
#define ACK "\x06"
#define EOT "\x04"
#define STX "\x02"
#define ETX "\x03"
#define ETB "\x17"
#define CR "\x0D"
#define LF "\x0A"
#define NAK "\x15"
#define FN "\x31"

/*
#define ENQ '\x05'
#define ACK '\x06'
#define EOT '\x04'
#define STX '\x02'
#define ETX '\x03'
#define ETB '\x17'
#define CR '\x0D'
#define LF '\x0A'
#define NAK '\x15'
#define FN '\x31'
*/
Server::Server()
{
    if(this->listen(QHostAddress::Any, 44)){
        qDebug() << "start server";
    }
    else {
        qDebug() << "error";
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    Sockets.push_back(socket);
    qDebug() << "client connected" << socketDescriptor;
}

void Server::slotReadyRead()
{
    //socket = (QTcpSocket*)sender();
    QByteArray arr_receivedData;
    arr_receivedData.clear();
    arr_receivedData = socket->readAll();
    qDebug() << "prishoooo v servera" << arr_receivedData <<  arr_receivedData.size();
    this->writeComand(ENQ);
    /*
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_7);
    if(in.status() == QDataStream::Ok){
        qDebug() << "read...";
        QString str;
        in >> str;
        qDebug() << str;
        //sendToClient(str);
        this->writeComand(ENQ);
    }
    else {
        qDebug() << "DataStream error";
    } 
    */

}

void Server::sendToClient(QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out << str;
    socket->write(Data);
    qDebug() << "Data posle out str" << Data;
}

void Server::writeComand(const char *comand)
{

    QByteArray send_data;
    send_data.clear();
    QDataStream out(&send_data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    quint8 b = 0x03;
    quint8 b2 = 0x05;
    out << b << b2;
    socket->write(send_data);
    qDebug() << "writeComand arr" << send_data << send_data.size();


}
