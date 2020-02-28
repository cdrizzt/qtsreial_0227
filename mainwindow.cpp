#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myserial = NULL;
    mytcp    = new myTCP(ui->portsetweight);

    portopen_en=false;
    Timer0_Init(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Timer0_Init(uint16_t time)
{
    myTime_0 = new QTimer();
    myTime_0->stop();
    myTime_0->setInterval(time);
    connect(myTime_0,SIGNAL(timeout()),this,SLOT(time0_task(void)));
    myTime_0->start();

}


void MainWindow::time0_task(void)
{
    QStringList port_num;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        port_num += info.portName()+"  "+info.description();
    }
    if(port_num.size()!=serialport_list.size()&&portopen_en==false)
    {
        QStringList same;
        QStringList diff_now,diff_last;
        //比较出相同项及增加项
        for(uint8_t i=0;i<port_num.size();i++)
        {
            bool flag=false;
            for(uint8_t j=0;j<serialport_list.size();j++)
            {
                if(port_num.value(i)==serialport_list.value(j))
                {
                    same<<port_num.value(i);
                    flag=true;
                    break;
                }
            }
            if(flag==false)
            {
                diff_now<<port_num.value(i);
            }
        }
        //比较出减少项并删除
        for(uint8_t i=0;i<serialport_list.size();i++)
        {
            bool flag=false;
            for(uint8_t j=0;j<same.size();j++)
            {
                if(serialport_list.value(i)==same.value(j))
                {
                   flag=true;
                   break;
                }
            }
            if(flag==false)
                ui->portchoose->removeItem(ui->portchoose->findText(serialport_list.value(i)));
        }
        ui->portchoose->addItems(diff_now);
        serialport_list=port_num;
        qDebug()<<port_num;
    }
}

void MainWindow::on_portchoose_currentIndexChanged(int index)
{
    if(portopen_en==false)
    {
        qDebug()<<index;
//        delete myserial;
        delete mytcp;

//        if(index==0) {mytcp    = new myTCP(ui->portsetweight); myserial=NULL;}
//        else{   myserial    = new mySerial(ui->portsetweight); mytcp=NULL;}

    }
}
