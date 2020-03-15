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
    //ui->setupUi(this);
}
