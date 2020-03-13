#include "oscilloscope.h"
#include "ui_oscilloscope.h"

oscilloscope::oscilloscope(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::oscilloscope)
{
    ui->setupUi(this);
}

oscilloscope::~oscilloscope()
{
    delete ui;
}
