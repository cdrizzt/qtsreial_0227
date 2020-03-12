#ifndef MYEXTEND_H
#define MYEXTEND_H

#include <QDialog>

namespace Ui {
class myextend;
}

class myextend : public QDialog
{
    Q_OBJECT

public:
    myextend(QWidget *parent = 0);
    ~myextend();
    bool open_flag;

private:
    Ui::myextend *ui;
};

#endif // MYEXTEND_H
