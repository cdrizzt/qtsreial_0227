﻿#include "oscilloscope.h"
#include "ui_oscilloscope.h"
#include "math.h"
#include <QDebug>
#include <QMouseEvent>
oscilloscope::oscilloscope(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::oscilloscope)
{

    ui->setupUi(this);

    for(int i=0;i<6;i++){
         //线
         data_num[i] = 0;
         data[i]     = new QLineSeries();
         data[i]->clear();
        //离散点
         myscatterseries[i] = new QScatterSeries();
         myscatterseries[i]->setMarkerShape(QScatterSeries::MarkerShapeCircle);//圆形的点
         myscatterseries[i]->setMarkerSize(7); //离散点大小
         myscatterseries[i]->clear();
     }

    myscatterseries[0]->setBorderColor(QColor(Qt::red));        //离散点边框颜色
    myscatterseries[0]->setBrush(QBrush(QColor(Qt::red)));      //离散点背景色

    set_mod = new oscset(this,&show_x.origin,&show_x.scope,&show_y.origin,&show_y.scope);//初始化设置
    mychart = new QChart();

    mychart->legend()->hide();

    ui->show1->setCheckState(Qt::Checked);
    ui->show2->setCheckState(Qt::Checked);
    ui->show3->setCheckState(Qt::Checked);
    ui->show4->setCheckState(Qt::Checked);
    ui->show5->setCheckState(Qt::Checked);
    ui->show6->setCheckState(Qt::Checked);

    ui->comboBox_1->setCurrentIndex(1);
    ui->comboBox_2->setCurrentIndex(1);
    ui->comboBox_3->setCurrentIndex(1);
    ui->comboBox_4->setCurrentIndex(1);
    ui->comboBox_5->setCurrentIndex(1);
    ui->comboBox_6->setCurrentIndex(1);

    for(int i=0;i<6;i++){
        mychart->addSeries(data[i]);
        mychart->addSeries(myscatterseries[i]);
    }

    show_y.min    = -1;
    show_y.max    = 1;
    show_y.scope=(show_y.max-show_y.min)*1.1;
    show_y.origin=(show_y.min+show_y.max)/2-show_y.scope/2;

    axisY = new QValueAxis();
    axisY->setRange(show_y.origin,show_y.origin+show_y.scope);

    show_x.origin      = 0;
    show_x.scope       = 100;
    show_x.max         = 100;
    axisX = new QValueAxis();
    axisX->setRange(show_x.origin,show_x.origin+show_x.scope);

    for(int i=0;i<6;i++){
        mychart->setAxisX(axisX,data[i]);
        mychart->setAxisY(axisY,data[i]);
        mychart->setAxisX(axisX,myscatterseries[i]);
        mychart->setAxisY(axisY,myscatterseries[i]);
    }


    QHBoxLayout *hb = new QHBoxLayout(ui->viewwidget);
    mychartvier = new myqchartview(mychart);
    hb->addWidget(mychartvier);
    mychart->setAcceptHoverEvents(true);


    connect(data[0],&QLineSeries::hovered, this,&oscilloscope::data_chovered);
    connect(data[0],&QLineSeries::clicked, this,&oscilloscope::data_clicked);
    connect(data[0],&QLineSeries::doubleClicked, this,&oscilloscope::data_clicked);

    connect(mychartvier,&myqchartview::chart_move,this,&oscilloscope::chart_move);
    connect(mychartvier,&myqchartview::zoom_moev,this,&oscilloscope::zoom_moev);
    connect(set_mod,&oscset::renew_window,this,&oscilloscope::renew_window);

    mychartvier->setMouseTracking(true);
}

oscilloscope::~oscilloscope()
{
    for(int i=0;i<6;i++){
        delete data[i];
        delete myscatterseries[i];} //示波器数据
    delete mychart;                 //实例
    delete mychartvier;             //画布
    delete axisX;
    delete axisY;
    delete ui;
}
void oscilloscope::data_chovered(QPointF point,bool flag)
{

    if(flag == true){       //绘图  弹出显示窗
        qDebug()<<point;
    }
    else{                   //清空

    }
}
void oscilloscope::data_clicked(QPointF point)
{
    QPointF real = MouseToSeries(point,0,0);
    myscatterseries[0]->append(real);
    qDebug()<<point<<real;

}

QByteArray oscilloscope::data_dispose(QByteArray indata)//数据处理函数
{
QByteArray a;
return a;

}
QPointF oscilloscope::MouseToSeries(QPointF FromMouse,int num,int mode)
{
    if(num>5) return FromMouse;
    if(FromMouse.x()<0)
        FromMouse.setX(0);

    for(int i =0;i<data_num[num]-2;i++){
        if((FromMouse.x() >= data[num]->at(i).x())&&
             (FromMouse.x() <= data[num]->at(i+1).x()))
        {
            qDebug()<<data[num]->at(i)<<data[num]->at(i+1)<<FromMouse;

            //qreal y = (data[num]->at(i).y()+data[num]->at(i+1).y())/2;
            qreal y = data[num]->at(i).y();
            qreal percentage = FromMouse.x()-data[num]->at(i).x();
            qreal variation = data[num]->at(i+1).y() - data[num]->at(i).y();

            y += percentage*variation;
            FromMouse.setY(y);
            return FromMouse;
        }
    }

    qreal y = data[num]->at(data_num[num]-1).y();
    FromMouse.setY(y);

    return FromMouse;
}
void oscilloscope::renew_window()
{
    ui->comboBox_1->setCurrentIndex(set_mod->agree[0].databit);
    ui->comboBox_2->setCurrentIndex(set_mod->agree[1].databit);
    ui->comboBox_3->setCurrentIndex(set_mod->agree[2].databit);
    ui->comboBox_4->setCurrentIndex(set_mod->agree[3].databit);
    ui->comboBox_5->setCurrentIndex(set_mod->agree[4].databit);
    ui->comboBox_6->setCurrentIndex(set_mod->agree[5].databit);

    axisX->setRange(show_x.origin,show_x.origin+show_x.scope);
    ui->xSlider->setValue((show_x.origin/(show_x.max-show_x.scope))*100);

    axisY->setRange(show_y.origin,show_y.origin+show_y.scope);
}
void oscilloscope::add_data(int num,uint32_t data_read)//数据显示函数
{
    float a=0;
    memcpy(&a,&data_read,sizeof(a));
    switch(num)
    {
        case 0:
        {
            data[0]->append(QPointF(data_num[0],a));
            data_num[0]++;
        }break;
        case 1:
        {
            data[1]->append(QPointF(data_num[1],a));
            data_num[1]++;
        }break;
        default:break;
    }
    if(data_num[num]>show_x.max){
        show_x.max++;
    }
    if(show_y.max<a){
        show_y.max=a;
    }
    if(show_y.min>a){
         show_y.min=a;
    }

    if(set_mod->asixl.follow==true)
    {
        if(set_mod->asixl.follow_x==true)
        {
            if(data_num[num]>show_x.max-0.1*show_x.scope)
            {
                show_x.origin = show_x.max-0.9*show_x.scope;
                axisX->setRange(show_x.origin,show_x.origin+show_x.scope);
                ui->xSlider->setValue((show_x.origin/(show_x.max-show_x.scope))*100);
            }
        }
        if(set_mod->asixl.follow_y==true)
        {
            show_y.scope=(show_y.max-show_y.min)*1.1;
            show_y.origin=(show_y.min+show_y.max)/2-show_y.scope/2;
            axisY->setRange(show_y.origin,show_y.origin+show_y.scope);
        }
    }
}
void oscilloscope::chart_move(QPoint move)                      //移动位置函数
{
    set_mod->asixl.follow=false;

    mychart->scroll(-move.x(),move.y());

    show_x.origin=axisX->min();
    show_y.origin = axisY->min();

    ui->xSlider->setValue((show_x.origin/(show_x.max-show_x.scope))*100);
}
void oscilloscope::zoom_moev(qreal delat, QPoint pos)           //放大函数
{
    set_mod->asixl.follow=false;

    QRectF old_area    = mychart->plotArea();
    QPointF old_center = old_area.center();

    qreal rVal = std::pow(0.999,delat);         //0.999 的n次幂

    old_area.setWidth(old_area.width()*rVal);  //缩放
    old_area.setHeight(old_area.height()*rVal);

    QPointF new_center = (2*old_center-pos-(old_center-pos)/rVal);
    old_area.moveCenter(new_center);
    mychart->zoomIn(old_area);

    show_x.origin = axisX->min();
    show_x.scope = axisX->max()-show_x.origin;

    show_y.scope =  axisY->max()-axisY->min();
    show_y.origin = axisY->min();

    ui->xSlider->setValue((show_x.origin/(show_x.max-show_x.scope))*100);

}

void oscilloscope::on_pushButton_4_clicked()
{
    set_mod->open();
}

void oscilloscope::on_xSlider_sliderMoved(int value)
{
    show_x.origin = (show_x.max-show_x.scope)*(float(value)/100);
    axisX->setRange(show_x.origin,show_x.origin+show_x.scope);

}

void oscilloscope::on_show1_clicked(bool checked)
{
    if(checked==true)
    {
        mychart->addSeries(data[0]);
        mychart->setAxisX(axisX,data[0]);
        mychart->setAxisY(axisY,data[0]);
    }
    else
    {
        mychart->removeSeries(data[0]);
    }
}

void oscilloscope::on_show2_clicked(bool checked)
{
    if(checked==true)
    {
        mychart->addSeries(data[1]);
        mychart->setAxisX(axisX,data[1]);
        mychart->setAxisY(axisY,data[1]);
    }
    else
    {
        mychart->removeSeries(data[1]);
    }
}

void oscilloscope::on_show3_clicked(bool checked)
{
    if(checked==true)
    {
        mychart->addSeries(data[2]);
        mychart->setAxisX(axisX,data[2]);
        mychart->setAxisY(axisY,data[2]);
    }
    else
    {
        mychart->removeSeries(data[2]);
    }
}

void oscilloscope::on_show4_clicked(bool checked)
{
    if(checked==true)
    {
        mychart->addSeries(data[3]);
        mychart->setAxisX(axisX,data[3]);
        mychart->setAxisY(axisY,data[3]);
    }
    else
    {
        mychart->removeSeries(data[3]);
    }
}

void oscilloscope::on_show5_clicked(bool checked)
{
    if(checked==true)
    {
        mychart->addSeries(data[4]);
        mychart->setAxisX(axisX,data[4]);
        mychart->setAxisY(axisY,data[4]);
    }
    else
    {
        mychart->removeSeries(data[4]);
    }
}

void oscilloscope::on_show6_clicked(bool checked)
{
    if(checked==true)
    {
        mychart->addSeries(data[5]);
        mychart->setAxisX(axisX,data[5]);
        mychart->setAxisY(axisY,data[5]);
    }
    else
    {
        mychart->removeSeries(data[5]);
    }
}

void oscilloscope::on_pushButton_2_clicked()
{
    for(int i=0;i<6;i++)
    {
        myscatterseries[i]->clear();
        data[i]->clear();
        data_num[i]=0;
    }
    show_y.min    = -1;
    show_y.max    = 1;
    show_y.scope=(show_y.max-show_y.min)*1.1;
    show_y.origin=(show_y.min+show_y.max)/2-show_y.scope/2;
    axisY->setRange(show_y.origin,show_y.origin+show_y.scope);

    show_x.origin      = 0;
    show_x.scope       = 100;
    show_x.max         = 100;
    axisX->setRange(show_x.origin,show_x.origin+show_x.scope);
}

void oscilloscope::on_datashow_renew_clicked()
{
    set_mod->asixl.follow=true;

    if(set_mod->asixl.follow_x==true)
    {
        show_x.origin = show_x.max-(show_x.scope*0.9);
        axisX->setRange(show_x.origin,show_x.origin+show_x.scope);
        ui->xSlider->setValue((show_x.origin/(show_x.max-show_x.scope))*100);
    }

    if(set_mod->asixl.follow_y==true)
    {
        show_y.scope=(show_y.max-show_y.min)*1.1;
        show_y.origin=(show_y.min+show_y.max)/2-show_y.scope/2;
        axisY->setRange(show_y.origin,show_y.origin+show_y.scope);
    }
}

void oscilloscope::on_comboBox_1_currentIndexChanged(int index)
{
    set_mod->agree[0].databit=index;
}

void oscilloscope::on_comboBox_2_currentIndexChanged(int index)
{
    set_mod->agree[1].databit=index;
}

void oscilloscope::on_comboBox_3_currentIndexChanged(int index)
{
    set_mod->agree[2].databit=index;
}

void oscilloscope::on_comboBox_4_currentIndexChanged(int index)
{
    set_mod->agree[3].databit=index;
}

void oscilloscope::on_comboBox_5_currentIndexChanged(int index)
{
    set_mod->agree[4].databit=index;
}

void oscilloscope::on_comboBox_6_currentIndexChanged(int index)
{
    set_mod->agree[5].databit=index;
}



void oscilloscope::on_pushButton_5_clicked()
{
    static bool flag = false;
    if(flag==false)
    {
        ui->pushButton_5->setText("启动");
        set_mod->asixl.follow=false;
    }
    else
    {
        ui->pushButton_5->setText("停止");
        set_mod->asixl.follow=true;
        show_x.origin = show_x.max-(show_x.scope*0.9);
        axisX->setRange(show_x.origin,show_x.origin+show_x.scope);

        ui->xSlider->setValue((show_x.origin/(show_x.max-show_x.scope))*100);
    }
    flag=!flag;
}
