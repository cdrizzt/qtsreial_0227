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

void myextend::on_open_osc_clicked()
{
    static bool flag=false;
    if(flag==true){
        emit open_osc();
    }
    else{
        emit close_osc();
    }
    flag=!flag;
}
