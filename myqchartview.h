#ifndef MYQCHARTVIEW_H
#define MYQCHARTVIEW_H

#include <QObject>
#include <QtCharts>
#include <QPoint>
#include <QPointF>
using namespace QtCharts;

class myqchartview: public QChartView
{
    Q_OBJECT
public:
    myqchartview(QWidget *parent = 0);
    myqchartview(QChart *chart, QWidget *parent = 0);
    ~myqchartview();

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void myqchartview::wheelEvent(QWheelEvent *event);
signals:
    chart_move(QPoint move);
    zoom_moev(QPoint pos);

private:
    QPoint StartPos;
};

#endif // MYQCHARTVIEW_H
