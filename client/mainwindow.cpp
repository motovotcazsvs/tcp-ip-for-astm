#include "mainwindow.h"
#include "ui_mainwindow.h"

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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkComand(unsigned char comand)
{
    if(arr_receivedData.size() != 1){
        if(arr_receivedData[0] != STX) {
            qDebug() << "очищаем массив на прием, потомушо первый символ не STX";
            arr_receivedData.clear();//только для посылок с началом STX, нада доделать и для DC1, DC2...
        }
        qDebug() << "return false, checkComand, в масиве на прием много символов";
        return false;
    }
    unsigned char c_temp = arr_receivedData[0];
    if(comand != ENQ){
        qDebug() << "очищаем массив dataReceive!";
        arr_receivedData.clear();
    }
    if(comand == c_temp){
        return true;
    }
    else return false;
}



void MainWindow::slotReadyRead()
{
    arr_receivedData.clear();
    arr_receivedData = socket->readAll();
    qDebug() << "prishoooo" << arr_receivedData << arr_receivedData.size();
    QString str;
    str.append(arr_receivedData);
    ui->textBrowser->append(str);
    /*
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_7);
    if(in.status() == QDataStream::Ok){
        arr_receivedData.clear();
        QString str;
        quint8 b;
        quint8 b2;
        //unsigned char

        in >> b >> b2;
        qDebug() << "prishoooo" << b << b2;
        //if(b == ENQ) qDebug() << "poluchil ENQ";

        //in >> b;
        //arr_receivedData = str.toLocal8Bit();
        //qDebug() << "str po priemu u klienta" << str.toUtf8() << endl;
        qDebug() << "prishoooo" << arr_receivedData << arr_receivedData.size();
        ui->textBrowser->append(str);
        if(str.at(0) == ENQ && str.size() == 1) qDebug() << "prisho enq";
        else qDebug() << "ne prishlo enq";
        qDebug() << "str po priemu u klienta" << str << endl;
        if(this->checkComand(ENQ)) qDebug() << "prishol enq";
        else qDebug() << "ne prishlo";
    }
    else {
        ui->textBrowser->append("read error");
    }
        */
}

void MainWindow::on_pushButton_clicked()
{
    /*
    if(socket->error() != -1){

        qDebug() << "not connect" << socket->error();
        return;
    }
*/

    socket->connectToHost("192.168.0.106", 44);
}

void MainWindow::sendToServer(QString str)
{
    QByteArray Dat;
    Dat.clear();
    QDataStream out_tcp(&Dat, QIODevice::WriteOnly);
    out_tcp.setVersion(QDataStream::Qt_5_7);
    QByteArray ba;
    ba.append(str);
    foreach (quint8 b, ba) {
        out_tcp << b;
    }


    socket->write(Dat);

    ui->lineEdit->clear();

    qDebug() << "Dat posle out str" << Dat;
}

void MainWindow::on_pushButton_2_clicked()
{
    sendToServer(ui->lineEdit->text());
}

void MainWindow::on_lineEdit_returnPressed()
{
    sendToServer(ui->lineEdit->text());
}


void MainWindow::on_pushButton_3_clicked()
{
    socket->disconnectFromHost();
    socket->~QTcpSocket();
    socket = new QTcpSocket(this);
}
