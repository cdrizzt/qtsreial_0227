#include "myextend.h"
#include "ui_myextend.h"

myextend::myextend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myextend)
{
    open_flag=false;
    ui->setupUi(this);
}

myextend::~myextend()
{
    delete ui;
}
