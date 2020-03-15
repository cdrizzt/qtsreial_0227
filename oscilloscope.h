#ifndef OSCILLOSCOPE_H
#define OSCILLOSCOPE_H

#include <QWidget>
#include <QtCharts>

#include "oscset.h"

namespace Ui {
class oscilloscope;
}
typedef struct{
    qreal max;
    qreal scope;
    qreal origin;
}axis_show;
using namespace QtCharts;
class oscilloscope : public QWidget
{
    Q_OBJECT

public:
    explicit oscilloscope(QWidget *parent = 0);
    void add_data(int num, uint32_t data_read);
    ~oscilloscope();

private slots:
    void on_xSlider_sliderMoved(int position);

    void on_pushButton_4_clicked();

private:
    oscset      *set_mod;
    QLineSeries *data;          //示波器数据
    uint32_t   data_num;

    QChart     *mychart;        //实例
    QChartView *mychartvier;    //画布
    QValueAxis *axisX;
    QValueAxis *axisY;

    axis_show show_x;
    axis_show show_y;

    Ui::oscilloscope *ui;
};

#endif // OSCILLOSCOPE_H
