#include "oscset.h"
#include "ui_oscset.h"
oscset::oscset(QWidget *parent,qreal *x_1,qreal *x_2,qreal *y_1,qreal *y_2) :
    QDialog(parent),
    ui(new Ui::oscset)
{
    ui->setupUi(this);
    wheel=zoomALL;
    clickset.move_model=Right;
    asixl.x_begin=x_1;
    asixl.x_scope=x_2;
    asixl.y_begin=y_1;
    asixl.y_scope=y_2;
    asixl.follow=true;

    for(int i=0;i<6;i++)
    {
        agree[i].head_byte=2;
        agree[i].tail_byte=2;
        agree[i].head[0]=0xAA;
        agree[i].head[1]=i;

        agree[i].databit=1;//mode1 int16

        agree[i].tail[0]=~i;
        agree[i].tail[1]=0x55;

        agree[i].check_mode=0;
    }

}

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
    static qreal x1=0,x2=0,y1=0,y2=0;
    asixl_cache.x_begin=&x1;
    asixl_cache.x_scope=&x2;
    asixl_cache.y_begin=&y1;
    asixl_cache.y_scope=&y2;
    on_renew_btn_clicked();

    this->show();
}

void oscset::on_renew_btn_clicked()
{
    *asixl_cache.x_begin=0;
    *asixl_cache.x_scope=0;
    *asixl_cache.y_begin=0;
    *asixl_cache.y_scope=0;

    wheel_cache=wheel;
    asixl_cache.follow=asixl.follow;
    clickset_cache=clickset;

    switch(wheel_cache){
    case zoomX:ui->radioButton_2->setChecked(true);break;
    case zoomY:ui->radioButton->setChecked(true);break;
    case zoomALL:ui->radioButton_3->setChecked(true);break;
    case zoomNone:ui->radioButton_4->setChecked(true);break;
    }
    switch (clickset_cache.move_model) {
    case Left:ui->radioButton_5->setChecked(true);break;
    case Right:ui->radioButton_6->setChecked(true);break;
    }

    if(clickset_cache.put_label==true)
        ui->checkBox_2->setCheckState(Qt::Checked);

    if(clickset_cache.show_data==true)
        ui->checkBox->setCheckState(Qt::Checked);

    if(asixl_cache.follow==true)
        ui->radioButton_7->setChecked(true);

    ui->data1->write(agree[0]);
    ui->data2->write(agree[1]);
    ui->data3->write(agree[2]);
    ui->data4->write(agree[3]);
    ui->data5->write(agree[4]);
    ui->data6->write(agree[5]);

}

void oscset::on_cancle_btn_clicked()
{
    this->close();
}

void oscset::on_ok_btn_clicked()
{
    agree[0]=ui->data1->read();
    agree[1]=ui->data2->read();
    agree[2]=ui->data3->read();
    agree[3]=ui->data4->read();
    agree[4]=ui->data5->read();
    agree[5]=ui->data6->read();

    wheel=wheel_cache;
    clickset=clickset_cache;
    if(ui->lineEdit->text()!=NULL){
        *asixl.x_begin=ui->lineEdit->text().toFloat();}
    if(ui->lineEdit_2->text()!=NULL){
        *asixl.x_scope=ui->lineEdit_2->text().toFloat();}

    if(ui->lineEdit_3->text()!=NULL){
        *asixl.y_begin=ui->lineEdit_3->text().toFloat();}
    if(ui->lineEdit_4->text()!=NULL){
        *asixl.y_scope=ui->lineEdit_4->text().toFloat();}

    asixl.follow=asixl_cache.follow;

    emit renew_window();
    this->close();
}

void oscset::on_radioButton_2_clicked()
{
    wheel_cache=zoomX;
}

void oscset::on_radioButton_3_clicked()
{
    wheel_cache=zoomALL;
}

void oscset::on_radioButton_clicked()
{
    wheel_cache=zoomY;
}


void oscset::on_radioButton_4_clicked()
{
    wheel_cache=zoomNone;
}

void oscset::on_radioButton_5_clicked()
{
    clickset_cache.move_model=Left;
}

void oscset::on_radioButton_6_clicked()
{
    clickset_cache.move_model=Right;
}

void oscset::on_checkBox_clicked(bool checked)
{
    clickset_cache.show_data=checked;
}

void oscset::on_checkBox_2_clicked(bool checked)
{
    clickset_cache.put_label=checked;
}

void oscset::on_radioButton_7_clicked(bool checked)
{
    asixl_cache.follow=checked;
}
