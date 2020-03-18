#include "agreement.h"
#include "ui_agreement.h"
#include "bytechange.h"
#include <QDebug>
Agreement::Agreement(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Agreement)
{
    ui->setupUi(this);

    QRegExp regExp("[a-fA-F0-9 ]{11}");
    ui->head_edit->setValidator(new QRegExpValidator(regExp, this));
    ui->tailedit->setValidator(new QRegExpValidator(regExp, this));

//    connect(ui->head_edit,&QLineEdit::cursorPositionChanged,this,&Agreement::head_edit_dispose);
//    connect(ui->tailedit,&QLineEdit::cursorPositionChanged,this,&Agreement::tail_edit_dispose);
}

Agreement::~Agreement()
{
    delete ui;
}

void Agreement::write(Agree data)//打开写入
{
    QByteArray head;
    for(int i=0;i<data.head_byte;i++){
          head.append(data.head[i]);
    }

    QString head_str=hexToString(head);

    QByteArray tail;
    for(int i=0;i<data.tail_byte;i++){
          tail.append(data.tail[i]);
    }
    QString tail_str=hexToString(tail);

    ui->head_edit->setText(head_str);
    ui->tailedit->setText(tail_str);

    ui->databit->setCurrentIndex(data.databit);
    ui->checkmode->setCurrentIndex(data.check_mode);

    QRegExp regExp("[a-fA-F0-9 ]{11}");
    ui->head_edit->setValidator(new QRegExpValidator(regExp, this));
    ui->tailedit->setValidator(new QRegExpValidator(regExp, this));
}

Agree Agreement::read()          //ok读出
{
    Agree return_data;
    QByteArray head_;
    QByteArray tail_;
    QString str_head=ui->head_edit->text();
    QString str_tail=ui->tailedit->text();
    head_=QString2Hex(str_head);
    tail_=QString2Hex(str_tail);

    return_data.head_byte=head_.size();
    for(int i=0;i<return_data.head_byte;i++){
        return_data.head[i]=head_.at(i);
    }
    return_data.tail_byte=tail_.size();
    for(int i=0;i<tail_.size();i++){
        return_data.tail[i]=tail_.at(i);
    }

    return_data.databit=ui->databit->currentIndex();
    return_data.check_mode=ui->checkmode->currentIndex();
    return return_data;
}



