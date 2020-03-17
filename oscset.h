#ifndef OSCSET_H
#define OSCSET_H

#include <QDialog>
#include "agreement.h"

namespace Ui {
class oscset;
}

typedef enum{
 zoomX,
 zoomY,
 zoomALL,
 zoomNone
}wheelmode;

typedef enum{
    Left,
    Right
}Move_;

typedef struct{
    Move_ move_model;
    bool show_data;
    bool put_label;
}clickmode;

typedef struct{
    bool follow;
    qreal *x_begin;
    qreal *x_scope;
    qreal *y_begin;
    qreal *y_scope;
}asix_mode;

class oscset : public QDialog
{
    Q_OBJECT

public:
    explicit oscset(QWidget *parent = 0);
    explicit oscset(QWidget *parent,qreal *x_1,qreal *x_2,qreal *y_1,qreal *y_2);
    ~oscset();
    void open();

    wheelmode wheel;
    clickmode clickset;
    asix_mode asixl;
    Agree agree[6];


private slots:
    void on_renew_btn_clicked();

    void on_cancle_btn_clicked();

    void on_ok_btn_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_checkBox_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

    void on_radioButton_7_clicked(bool checked);

private:
    wheelmode wheel_cache;
    clickmode clickset_cache;
    asix_mode asixl_cache;
    Ui::oscset *ui;
};

#endif // OSCSET_H
