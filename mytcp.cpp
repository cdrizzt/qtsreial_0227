#include "mytcp.h"
#include "ui_mytcp_config.h"

myTCP::myTCP(QWidget *parent):
    ui_cfg(new Ui::mytcp_config)
{
    ui_cfg->setupUi(parent);
}
myTCP::~myTCP()
{
    delete ui_cfg;
}
