#include "oscset.h"
#include "ui_oscset.h"

oscset::oscset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::oscset)
{
    ui->setupUi(this);
}

oscset::~oscset()
{
    delete ui;
}

void oscset::open()
{

}

void oscset::on_renew_btn_clicked()
{

}

void oscset::on_cancle_btn_clicked()
{

}
