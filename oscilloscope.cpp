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

    for(int i=0;i<6;i++){
         data_num[i] = 0;
         data[i]     = new QLineSeries();
         data[i]->clear();
     }
    mychart = new QChart();
    mychart->legend()->hide();

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


    for(int i=0;i<6;i++){
        mychart->setAxisX(axisX,data[i]);
        mychart->setAxisY(axisY,data[i]);
    }


    QHBoxLayout *hb = new QHBoxLayout(ui->viewwidget);
    mychartvier = new myqchartview(mychart);
    hb->addWidget(mychartvier);

    connect(mychartvier,&myqchartview::chart_move,this,&oscilloscope::chart_move);
    connect(mychartvier,&myqchartview::zoom_moev,this,&oscilloscope::zoom_moev);
}

oscilloscope::~oscilloscope()
{
    for(int i=0;i<6;i++)
        {delete data;}          //示波器数据
    delete mychart;            //实例
    delete mychartvier;        //画布
    delete axisX;
    delete axisY;
    delete ui;
}

QByteArray oscilloscope::data_dispose(QByteArray indata)//数据处理函数
{


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
    for(int i=0;i<6;i++)
    {
        if(data_num[i]>show_x.max*0.9)
        {
            show_x.max+=1;
            show_x.origin+=1;
            axisX->setRange(show_x.origin,show_x.origin+show_x.scope);
            ui->xSlider->setValue((show_x.origin/(show_x.max-show_x.scope))*100);
            return;
        }

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
    set_mod->show();
}

void oscilloscope::on_xSlider_valueChanged(int value)
{
    show_x.origin = (show_x.max-show_x.scope)*(float(value)/100);
    axisX->setRange(show_x.origin,show_x.origin+show_x.scope);
}
