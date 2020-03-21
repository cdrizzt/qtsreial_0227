#include "myqchartview.h"
#include <QDebug>
myqchartview::myqchartview(QWidget *parent):QChartView(parent)
{
    painter = new QPainter(this);
    this->chart()->setAcceptHoverEvents(true);  //chart接收悬停事件
}
myqchartview::myqchartview(QChart *chart, QWidget *parent):QChartView(chart,parent)
{
    painter = new QPainter(this);
    this->chart()->setAcceptHoverEvents(true);
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
    qreal delta = event->angleDelta().y();
    QPoint pos = event->pos();
    emit zoom_moev(delta,pos);
}
void myqchartview::my_hoverevent(QPointF point, bool state)
{
//    QPen pen;
//    QPoint a(0,0);
//    pen.setColor(Qt::red);           // 设置画笔为黄色
//    painter->setPen(pen);                // 设置画笔
//    painter->drawLine(event->pos(),a);

    qDebug()<<"hover";
}
