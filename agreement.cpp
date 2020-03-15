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
