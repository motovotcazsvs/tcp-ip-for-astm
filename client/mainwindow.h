#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTcpSocket>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool checkComand(unsigned char);

public slots:
    void slotReadyRead();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_returnPressed();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

    QTcpSocket *socket;
    QByteArray Data;
    void sendToServer(QString);
    QByteArray arr_receivedData;
};

#endif // MAINWINDOW_H
