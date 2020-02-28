#ifndef MYSERIAL_H
#define MYSERIAL_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class myserial_config;
class myserial_set;
}


class mySerial :public QWidget
{
    Q_OBJECT

public:
    mySerial(QWidget *parent = 0);
    mySerial(QWidget *parent,QString com);
    ~mySerial();

private slots:
    void on_port_setin_clicked();

    void on_okbtn_clicked();

    void on_canclebtn_clicked();

    void on_baud_box_currentIndexChanged(const QString &arg1);

private:
    QDialog *setdialog;
    Ui::myserial_config *ui_cfg;
    Ui::myserial_set *ui_set;

    QStringList port_set;
};

#endif // MYSERIAL_H
