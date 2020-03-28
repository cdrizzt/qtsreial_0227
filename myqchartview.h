#ifndef MYQCHARTVIEW_H
#define MYQCHARTVIEW_H

#include <QObject>
#include <QtCharts>
#include <QPoint>
#include <QPainter>
#include <QtGui/QMouseEvent>
using namespace QtCharts;

class myqchartview: public QChartView
{
    Q_OBJECT
public:
    myqchartview(QWidget *parent = 0);
    myqchartview(QChart *chart, QWidget *parent = 0);
    ~myqchartview();

    virtual void mousePressEvent(QMouseEvent *event);   //点击
    virtual void mouseMoveEvent(QMouseEvent *event);    //移动
    virtual void wheelEvent(QWheelEvent *event);        //滚轮

signals:
    chart_move(QPoint move);
    zoom_moev(qreal delat, QPoint pos);

private:
    QPoint StartPos;
    QPainter *painter;
};

#endif // MYQCHARTVIEW_H
