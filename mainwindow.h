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
#include <QLabel>

#include "stdlib.h"
#include "string.h"

#include "myextend.h"
#include "myserial.h"
#include "mytcp.h"
#include "bytechange.h"
#include "oscilloscope.h"

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

    void Timer0_Init(uint16_t time);       //中断时间
    void Timer1_Init(uint16_t time);       //中断时间
    void Timer2_Init(uint16_t time);       //中断时间
    void Timerread_Init(uint16_t time);       //中断时间
    void edit_show(QByteArray byte_, uint8_t flag);
    void MesStatusBar();
private slots:          //槽
    void time0_task(void);
    void time1_task(void);
    void time2_task(void);
    void timeread_task(void);
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
    void on_cleansendbtn_clicked();
    void on_filesendstopbtn_clicked();
    void on_pushButton_clicked();
    void open_osci();
    void close_osci();

private:
    bool portopen_en;
    int read_dalay;
    QByteArray  read_show;
    QByteArray  senddata_num;
    QByteArray  readdata_num;
    SendStatus sendsta;
    ReciveStatus receivesta;

    Ui::MainWindow *ui;
    oscilloscope *myosc;
    myextend   *extend;
    mySerial *myserial;
    myTCP    *mytcp;
    QTimer   *myTime_read;
    QTimer   *myTime_0;
    QTimer   *myTime_1;
    QTimer   *myTime_2;
    QFile    *send_save_file;
    QLabel   *label_send;
    QLabel   *label_rec;
    QFont    *send_font;
    QFont    *receive_font;

    QStringList serialport_list;     //串口端口号
};

#endif // MAINWINDOW_H
