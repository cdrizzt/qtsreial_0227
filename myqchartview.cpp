#include "myqchartview.h"
#include <QDebug>
myqchartview::myqchartview(QWidget *parent):QChartView(parent)
{
    //this->setParent(parent);
}
myqchartview::myqchartview(QChart *chart, QWidget *parent):QChartView(chart,parent)
{

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

}
void myqchartview::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        StartPos = event->pos();
    }
}
void myqchartview::wheelEvent(QWheelEvent *event)
{
    event->delta()
    emit
}
