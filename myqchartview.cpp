#include "myqchartview.h"
#include <QDebug>
myqchartview::myqchartview(QWidget *parent):QChartView(parent)
{
    painter = new QPainter(this);
}
myqchartview::myqchartview(QChart *chart, QWidget *parent):QChartView(chart,parent)
{
    painter = new QPainter(this);
}
myqchartview::~myqchartview()
{

}

void myqchartview::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::RightButton)
    {
        QPoint errorPose = event->pos()-StartPos;
        StartPos=event->pos();
        emit chart_move(errorPose);
    }
    QChartView::mouseMoveEvent(event);

}
void myqchartview::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        StartPos = event->pos();
    }
    QChartView::mousePressEvent(event);

}
void myqchartview::wheelEvent(QWheelEvent *event)
{
    qreal delta = event->angleDelta().y();
    QPoint pos = event->pos();
    emit zoom_moev(delta,pos);

    QChartView::wheelEvent(event);
}
