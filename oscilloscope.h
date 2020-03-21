#ifndef OSCILLOSCOPE_H
#define OSCILLOSCOPE_H

#include <QWidget>
#include <QtCharts>
#include <QValueAxis>
#include <QPointF>
#include <QRectF>
#include "oscset.h"
#include "myqchartview.h"
namespace Ui {
class oscilloscope;
}
typedef struct{
    qreal min;
    qreal max;
    qreal scope;
    qreal origin;
}axis_show;
using namespace QtCharts;
class oscilloscope : public QDialog
{
    Q_OBJECT

public:
    explicit oscilloscope(QWidget *parent = 0);
    ~oscilloscope();

    void add_data(int num, uint32_t data_read);
    QByteArray data_dispose(QByteArray indata);



private slots:
    void chart_move(QPoint move);
    void zoom_moev(qreal delat,QPoint pos);
    void on_pushButton_4_clicked();

    void on_xSlider_sliderMoved(int value);


    void on_show1_clicked(bool checked);

    void on_show2_clicked(bool checked);

    void on_show3_clicked(bool checked);

    void on_show4_clicked(bool checked);

    void on_show5_clicked(bool checked);

    void on_show6_clicked(bool checked);

    void on_pushButton_2_clicked();

    void on_datashow_renew_clicked();

    void renew_window();
    void on_comboBox_1_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_3_currentIndexChanged(int index);

    void on_comboBox_4_currentIndexChanged(int index);

    void on_comboBox_5_currentIndexChanged(int index);

    void on_comboBox_6_currentIndexChanged(int index);

    void on_pushButton_5_clicked();

private:
    oscset      *set_mod;
    QLineSeries *data[6];            //示波器数据
    uint32_t   data_num[6];

    QChart     *mychart;          //实例
    myqchartview *mychartvier;    //画布
    QValueAxis *axisX;
    QValueAxis *axisY;

    axis_show show_x;
    axis_show show_y;

    Ui::oscilloscope *ui;
};

#endif // OSCILLOSCOPE_H
