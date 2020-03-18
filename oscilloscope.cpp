#include "oscilloscope.h"
#include "ui_oscilloscope.h"
#include "math.h"
#include <QDebug>
oscilloscope::oscilloscope(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::oscilloscope)
{
    ui->setupUi(this);

    for(int i=0;i<6;i++){
         data_num[i] = 0;
         data[i]     = new QLineSeries();
         data[i]->clear();
     }

    mychart = new QChart();
    mychart->legend()->hide();

    ui->show1->setCheckState(Qt::Checked);
    ui->show2->setCheckState(Qt::Checked);
    ui->show3->setCheckState(Qt::Checked);
    ui->show4->setCheckState(Qt::Checked);
    ui->show5->setCheckState(Qt::Checked);
    ui->show6->setCheckState(Qt::Checked);

    for(int i=0;i<6;i++){
        mychart->addSeries(data[i]);
    }

    show_y.origin = 0;
    show_y.scope  = 6;
    axisY = new QValueAxis();
    axisY->setRange(show_y.origin-show_y.scope/2,
                    show_y.origin+show_y.scope/2);

    show_x.origin      = 0;
    show_x.scope       = 100;
    show_x.max         = show_x.origin+show_x.scope;
    axisX = new QValueAxis();
    axisX->setRange(show_x.origin,show_x.origin+show_x.scope);

    set_mod = new oscset(this,&show_x.origin,&show_x.scope,&show_y.origin,&show_y.scope);//初始化设置

    for(int i=0;i<6;i++){
        mychart->setAxisX(axisX,data[i]);
        mychart->setAxisY(axisY,data[i]);
    }


    QHBoxLayout *hb = new QHBoxLayout(ui->viewwidget);
    mychartvier = new myqchartview(mychart);
    hb->addWidget(mychartvier);

    connect(mychartvier,&myqchartview::chart_move,this,&oscilloscope::chart_move);
    connect(mychartvier,&myqchartview::zoom_moev,this,&oscilloscope::zoom_moev);
    connect(set_mod,&oscset::renew_window,this,&oscilloscope::renew_window);
}

oscilloscope::~oscilloscope()
{
    for(int i=0;i<6;i++)
        {delete data[i];}          //示波器数据
    delete mychart;            //实例
    delete mychartvier;        //画布
    delete axisX;
    delete axisY;
    delete ui;
}

QByteArray oscilloscope::data_dispose(QByteArray indata)//数据处理函数
{


}
void oscilloscope::renew_window()
{
    axisX->setRange(show_x.origin,show_x.origin+show_x.scope);
    ui->xSlider->setValue((show_x.origin/(show_x.max-show_x.scope))*100);

    axisY->setRange(show_y.origin-show_y.scope/2,
                    show_y.origin+show_y.scope/2);
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
    for(int i=0;i<6;i++){
        if(data_num[i]>show_x.max)
        {
            show_x.max++;
            show_x.origin++;
        }
    }

    if(set_mod->asixl.follow==true)
    {
        axisX->setRange(show_x.origin,show_x.origin+show_x.scope);
        ui->xSlider->setValue((show_x.origin/(show_x.max-show_x.scope))*100);
    }
}
void oscilloscope::chart_move(QPoint move)
{
    mychart->scroll(-move.x(),move.y());
    show_x.origin=axisX->min();
    ui->xSlider->setValue((show_x.origin/(show_x.max-show_x.scope))*100);
}
void oscilloscope::zoom_moev(qreal delat, QPoint pos)
{
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
    show_y.origin = (axisY->max()+axisY->min())/2;

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
        data[i]->clear();
        data_num[i]=0;
    }
    show_y.origin = 0;
    show_y.scope  = 6;
    axisY->setRange(show_y.origin-show_y.scope/2,
                    show_y.origin+show_y.scope/2);

    show_x.origin      = 0;
    show_x.scope       = 100;
    show_x.max         = show_x.origin+show_x.scope;
    axisX->setRange(show_x.origin,show_x.origin+show_x.scope);
}

void oscilloscope::on_datashow_renew_clicked()
{
    show_x.scope       = 100;
    show_x.origin = show_x.max-(show_x.scope*0.9);
    axisX->setRange(show_x.origin,show_x.origin+show_x.scope);

    ui->xSlider->setValue((show_x.origin/(show_x.max-show_x.scope))*100);

    show_y.origin = 0;
    show_y.scope  = 6;
    axisY->setRange(show_y.origin-show_y.scope/2,
                    show_y.origin+show_y.scope/2);
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
