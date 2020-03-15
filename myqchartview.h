#ifndef MYQCHARTVIEW_H
#define MYQCHARTVIEW_H

#include <QObject>
#include <QtCharts>
#include <QPoint>
#include <QValueAxis>
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
signals:
   change_x(QValueAxis *x);
   change_y(QValueAxis *y);

private:
    QPoint StartPos;
};

#endif // MYQCHARTVIEW_H
