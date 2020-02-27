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
    if(port_num.size()!=serialport_list.size())
    {
        qDebug()<<port_num;
        serialport_list=port_num;
        ui->portchoose->clear();
        ui->portchoose->addItem("TCPClient");
        ui->portchoose->addItems(serialport_list);
    }
}

void MainWindow::on_portchoose_currentIndexChanged(int index)
{

}
