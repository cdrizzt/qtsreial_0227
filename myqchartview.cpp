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
        this->chart()->scroll(-errorPose.x(),errorPose.y());
        StartPos=event->pos();
        qDebug()<<StartPos;
        this->chart()->a
        emit change_x();
    }

}
void myqchartview::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        StartPos = event->pos();
    }
}
