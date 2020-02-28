#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QtSerialPort/QSerialPortInfo>
#include <stdio.h>


#include "myserial.h"
#include "mytcp.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void Timer0_Init(uint16_t time);       //中断时间 对象 槽函数

    bool portopen_en;
private slots:          //槽
    void time0_task(void);
    void on_portchoose_currentIndexChanged(int index);
private:
    Ui::MainWindow *ui;
    mySerial *myserial;
    myTCP    *mytcp;
    QTimer   *myTime_0;

    QStringList serialport_list;     //串口端口号
};

#endif // MAINWINDOW_H
