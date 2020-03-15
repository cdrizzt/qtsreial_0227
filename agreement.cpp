#include "agreement.h"
#include "ui_agreement.h"

Agreement::Agreement(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Agreement)
{
    ui->setupUi(this);
}

Agreement::~Agreement()
{
    delete ui;
}

void Agreement::write(Agree data)//打开写入
{

}

Agree Agreement::read()          //ok读出
{

}
