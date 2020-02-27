#ifndef MYSERIAL_H
#define MYSERIAL_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDialog>
namespace Ui {
class myserial_config;
class myserial_set;
}


class mySerial :public QObject
{
    Q_OBJECT

public:
    mySerial();
    ~mySerial();

private:
    Ui::myserial_config *ui_cfg;
    Ui::myserial_set *ui_set;

};

#endif // MYSERIAL_H
