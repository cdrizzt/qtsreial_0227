#ifndef OSCSET_H
#define OSCSET_H

#include <QDialog>
#include "agreement.h"

namespace Ui {
class oscset;
}

class oscset : public QDialog
{
    Q_OBJECT

public:
    explicit oscset(QWidget *parent = 0);
    ~oscset();
    void open();

private:
    Agree agreement[6];
    Ui::oscset *ui;
};

#endif // OSCSET_H
