#include "myserial.h"
#include "ui_myserial_config.h"
#include "ui_myserial_set.h"

mySerial::mySerial(QWidget *parent):
    ui_cfg(new Ui::myserial_config)
{
    ui_set = NULL;
    ui_cfg->setupUi(parent);

}
mySerial::~mySerial()
{
    delete ui_set;
    delete ui_cfg;
}
