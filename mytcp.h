#ifndef MYTCP_H
#define MYTCP_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

namespace Ui {
class mytcp_config;
}

class myTCP:public QObject
{
    Q_OBJECT
public:
    myTCP(QWidget *parent = 0);
     ~myTCP();

private:
    Ui::mytcp_config *ui_cfg;
};

#endif // MYTCP_H
