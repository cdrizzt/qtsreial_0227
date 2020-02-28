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
    ui_cfg->setupUi(this);
    this->show();

}
mySerial::mySerial(QWidget *parent,QString com):
    QWidget(parent),
    ui_cfg(new Ui::myserial_config)
{
    ui_set=NULL;
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
    delete setdialog;
    delete ui_set;
    delete ui_cfg;
}
void mySerial::on_port_setin_clicked()
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
    port_set.replace(1,arg1);
    qDebug()<<port_set;
}
