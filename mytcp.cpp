#include "mytcp.h"
#include "ui_mytcp_config.h"

#include <QDebug>
myTCP::myTCP(QWidget *parent):
    QWidget(parent),
    ui_cfg(new Ui::mytcp_config)
{
    ui_cfg->setupUi(this);
    this->show();
}
myTCP::~myTCP()
{
    qDebug()<<"delete";
    delete ui_cfg;
}
