#ifndef OSCILLOSCOPE_H
#define OSCILLOSCOPE_H

#include <QWidget>

namespace Ui {
class oscilloscope;
}

class oscilloscope : public QWidget
{
    Q_OBJECT

public:
    explicit oscilloscope(QWidget *parent = 0);
    ~oscilloscope();

private:
    Ui::oscilloscope *ui;
};

#endif // OSCILLOSCOPE_H
