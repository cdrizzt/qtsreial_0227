#ifndef MYEXTEND_H
#define MYEXTEND_H

#include <QDialog>

namespace Ui {
class myextend;
}

class myextend : public QDialog
{
    Q_OBJECT

signals:
    open_osc(void);
    close_osc(void);
public:
    myextend(QWidget *parent = 0);
    ~myextend();
    bool open_flag;

private slots:
    void on_open_osc_clicked();

private:
    Ui::myextend *ui;
};

#endif // MYEXTEND_H
