#include "oscilloscope.h"
#include "ui_oscilloscope.h"
#include "math.h"
#include <QDebug>
oscilloscope::oscilloscope(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::oscilloscope)
{
    ui->setupUi(this);

    set_mod = new oscset(this);

    data_num=0;
    data    = new QLineSeries();

    mychart = new QChart();
    mychart->legend()->hide();

    mychart->addSeries(data);

    show_x.origin = 0;
    show_x.scope       = 100;
    show_x.max         = show_x.origin+show_x.scope;

    axisX = new QValueAxis();
    axisX->setRange(show_x.origin,show_x.origin+show_x.scope);

    axisX->setTitleText("t/ms");

    show_y.origin = 0;
    show_y.scope       = 6;

    axisY = new QValueAxis();
    axisY->setRange(show_y.origin-show_y.scope/2,
                    show_y.origin+show_y.scope/2);

    axisY->setTitleText("au/mv");

    mychart->setAxisX(axisX,data);
    mychart->setAxisY(axisY,data);

    QHBoxLayout *hb = new QHBoxLayout(ui->viewwidget);
    mychartvier = new QChartView(mychart);
    hb->addWidget(mychartvier);

}

oscilloscope::~oscilloscope()
{
    delete data;          //示波器数据
    delete mychart;            //实例
    delete mychartvier;    //画布
    delete axisX;
    delete axisY;
    delete ui;
}

void oscilloscope::add_data(int num,uint32_t data_read)
{

    float a=0;
    memcpy(&a,&data_read,sizeof(a));
    switch(num)
    {
        case 0:
        {
            data_num++;
            data->append(QPointF(data_num,a));
        }break;
        default:break;
    }
    if(data_num>show_x.max*0.9)
    {
        show_x.max+=1;
        show_x.origin+=1;
        axisX->setRange(show_x.origin,show_x.origin+show_x.scope);
    }
}

void oscilloscope::on_xSlider_sliderMoved(int position)
{
    show_x.origin = (show_x.max-show_x.scope)*(float(position)/100);
    axisX->setRange(show_x.origin,show_x.origin+show_x.scope);
}

void oscilloscope::on_pushButton_4_clicked()
{
    set_mod->show();
}
