#include "myserial.h"
#include "ui_myserial_config.h"
#include "ui_myserial_set.h"

#include <QDebug>

mySerial::mySerial(QWidget *parent):
    QWidget(parent),
    ui_cfg(new Ui::myserial_config)
{
    ui_set = NULL;
    setdialog = NULL;
    SerialPort = NULL;
    ui_cfg->setupUi(this);
    this->show();

}
mySerial::mySerial(QWidget *parent,QString com):
    QWidget(parent),
    ui_cfg(new Ui::myserial_config)
{
    open_flag=false;
    ui_set = NULL;
    setdialog = NULL;
    SerialPort = NULL;
    ui_cfg->setupUi(this);
    this->show();

    port_set.clear();
    port_set<<com;
    port_set<<"115200";
    port_set<<"8";
    port_set<<"1";
    port_set<<"None";
    port_set<<"None";

    ui_cfg->baud_box->setCurrentIndex(ui_cfg->baud_box->findText(port_set.value(1)));

}

mySerial::~mySerial()
{
    delete SerialPort;
    delete setdialog;
    delete ui_set;
    delete ui_cfg;
}
void mySerial::stopsend()
{
    SerialPort->clear(QSerialPort::Output);
}
void mySerial::on_port_setin_clicked()
{
    if(open_flag==false)
    {
        qDebug()<<"open";

        setdialog = new QDialog(this);
        ui_set = new Ui::myserial_set;
        ui_set->setupUi(setdialog);
        ui_set->port_box->addItem(port_set.value(0));
        ui_set->baud_box->setCurrentIndex(ui_set->baud_box->findText(port_set.value(1)));
        ui_set->data_box->setCurrentIndex(ui_set->data_box->findText(port_set.value(2)));
        ui_set->stopbox->setCurrentIndex(ui_set->stopbox->findText(port_set.value(3)));
        ui_set->paritybox->setCurrentIndex(ui_set->paritybox->findText(port_set.value(4)));
        ui_set->controlbox->setCurrentIndex(ui_set->controlbox->findText(port_set.value(5)));

        connect(ui_set->okbtn,&QPushButton::clicked,this,&mySerial::on_okbtn_clicked);
        connect(ui_set->canclebtn,&QPushButton::clicked,this,&mySerial::on_canclebtn_clicked);

        setdialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        setdialog->setWindowModality(Qt::WindowModal);
        setdialog->show();
        setdialog->exec();
    }
    else    //警告
    {

    }
}

void mySerial::on_okbtn_clicked()
{
    port_set.clear();
    port_set<<ui_set->port_box->currentText();
    port_set<<ui_set->baud_box->currentText();
    port_set<<ui_set->data_box->currentText();
    port_set<<ui_set->stopbox->currentText();
    port_set<<ui_set->paritybox->currentText();
    port_set<<ui_set->controlbox->currentText();

    qDebug()<<port_set;

    delete setdialog;   setdialog=NULL;
    delete ui_set;      ui_set=NULL;

    ui_cfg->baud_box->setCurrentIndex(ui_cfg->baud_box->findText(port_set.value(1)));
}

void mySerial::on_canclebtn_clicked()
{
    delete setdialog;   setdialog=NULL;
    delete ui_set;      ui_set=NULL;
    qDebug()<<"close";
}

void mySerial::on_baud_box_currentIndexChanged(const QString &arg1)
{
    if(open_flag==false)
    {
        port_set.replace(1,arg1);
        qDebug()<<port_set;
    }
    else    //警告窗口
    {

    }

}

void mySerial::on_serialswitch_clicked()
{
    if(open_flag==false)
    {
        SerialPort = new QSerialPort;
        SerialPort->setPortName(port_set.value(0));
        if(SerialPort->open(QIODevice::ReadWrite))
        {
            qDebug()<<"open";
            //波特率
            {
            if(port_set.value(1)=="1200")
                SerialPort->setBaudRate(QSerialPort::Baud1200);
            else if(port_set.value(1)=="2400")
                SerialPort->setBaudRate(QSerialPort::Baud2400);
            else if(port_set.value(1)=="4800")
                SerialPort->setBaudRate(QSerialPort::Baud4800);
            else if(port_set.value(1)=="9600")
                SerialPort->setBaudRate(QSerialPort::Baud9600);
            else if(port_set.value(1)=="19200")
                SerialPort->setBaudRate(QSerialPort::Baud19200);
            else if(port_set.value(1)=="38400")
                SerialPort->setBaudRate(QSerialPort::Baud38400);
            else if(port_set.value(1)=="57600")
                SerialPort->setBaudRate(QSerialPort::Baud57600);
            else if(port_set.value(1)=="115200")
                SerialPort->setBaudRate(QSerialPort::Baud115200);
            }
            //数据位
            {
                if(port_set.value(2)=="5")
                    SerialPort->setDataBits(QSerialPort::Data5);
                else if(port_set.value(2)=="6")
                    SerialPort->setDataBits(QSerialPort::Data6);
                else if(port_set.value(2)=="7")
                    SerialPort->setDataBits(QSerialPort::Data7);
                else if(port_set.value(2)=="8")
                    SerialPort->setDataBits(QSerialPort::Data8);
            }
            //停止位
            {
                if(port_set.value(3)=="1")
                    SerialPort->setStopBits(QSerialPort::OneStop);
                else if(port_set.value(3)=="1.5")
                    SerialPort->setStopBits(QSerialPort::OneAndHalfStop);
                else if(port_set.value(3)=="2")
                    SerialPort->setStopBits(QSerialPort::TwoStop);
            }
            //校验位
            {
                if(port_set.value(4)=="None")
                    SerialPort->setParity(QSerialPort::NoParity);
                else if(port_set.value(4)=="odd")
                    SerialPort->setParity(QSerialPort::OddParity);
                else if(port_set.value(4)=="even")
                    SerialPort->setParity(QSerialPort::EvenParity);
                else if(port_set.value(4)=="space")
                    SerialPort->setParity(QSerialPort::SpaceParity);
                else if(port_set.value(4)=="mark")
                    SerialPort->setParity(QSerialPort::MarkParity);
            }
            //控制流
            {
                if(port_set.value(5)=="None")
                     SerialPort->setFlowControl(QSerialPort::NoFlowControl);
                else if(port_set.value(5)=="Hardware")
                     SerialPort->setFlowControl(QSerialPort::HardwareControl);
                else if(port_set.value(5)=="Software")
                     SerialPort->setFlowControl(QSerialPort::SoftwareControl);
            }


            //关闭菜单使能
            ui_cfg->baud_box->setEnabled(false);
            ui_cfg->port_setin->setEnabled(false);
            //链接槽函数

            connect(SerialPort,&QSerialPort::readyRead,this,&mySerial::read_data);

            ui_cfg->serialswitch->setText("关闭串口");
            open_flag=true;
        }
        else        //警告窗口
        {
            qDebug()<<"false";
        }
    }
    else
    {
        qDebug()<<"close";
        ui_cfg->baud_box->setEnabled(true);
        ui_cfg->port_setin->setEnabled(true);
        delete SerialPort;  SerialPort = NULL;
        ui_cfg->serialswitch->setText("打开串口");
        open_flag=false;
    }
    emit serial_status(open_flag);
}
void mySerial::read_data()
{
    QByteArray buf;
    buf = SerialPort->readAll();
    if(!buf.isEmpty())
    {
        emit serial_readdata(buf);
    }
}
void mySerial::send_data(QByteArray buf)
{
    SerialPort->write(buf);
}
