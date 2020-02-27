#include "myserial.h"

mySerial::mySerial()
{
    ui_set = NULL;
    ui_cfg = NULL;
}
mySerial::~mySerial()
{
    delete ui_set;
    delete ui_cfg;
}
