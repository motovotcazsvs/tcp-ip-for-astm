#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server();
    QTcpSocket *socket;
    void writeComand(const char *);

private:
    QVector <QTcpSocket*> Sockets;
    QByteArray Data;
    void sendToClient(QString str);

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();



};

#endif // SERVER_H
