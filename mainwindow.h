#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QtSerialPort/QSerialPortInfo>
#include <stdio.h>
#include <QFile>
#include <QFileDialog>
#include <QFont>

#include "myserial.h"
#include "mytcp.h"
#include "bytechange.h"

typedef struct{
    bool hexshow;
    bool timeshow;
    bool filerecive;
}ReciveStatus;
typedef struct{
    bool hexsend;
    bool entersend;
    bool checksend;
    bool timersend;
    bool sendshow;
}SendStatus;

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
    void edit_show(QString str, uint8_t flag);

private slots:          //槽
    void time0_task(void);
    void changeportopen_en(bool flag);
    void send_data_serial(void);
    void send_data_tcp(void);
    void data_dispose(QByteArray str);
    void on_portchoose_currentIndexChanged(int index);
    void on_cleanrecivebtn_clicked();
    void sendedit_dispose();
    void on_savebtn_clicked();

    void on_topweight_clicked(bool checked);

    void on_Hexshow_clicked(bool checked);

    void on_Hexsend_clicked(bool checked);

    void on_RevicceToFile_clicked(bool checked);

    void on_sendOntime_clicked(bool checked);

    void on_timeshow_clicked(bool checked);

    void on_addlineend_clicked(bool checked);

    void on_addverify_clicked(bool checked);

    void on_sendshow_clicked(bool checked);

    void on_openfilebtn_clicked();

private:
    bool portopen_en;

    SendStatus sendsta;
    ReciveStatus receivesta;

    Ui::MainWindow *ui;
    mySerial *myserial;
    myTCP    *mytcp;
    QTimer   *myTime_0;

    QFont *send_font;
    QFont *receive_font;

    QStringList serialport_list;     //串口端口号
};

#endif // MAINWINDOW_H
