#include "agreement.h"
#include "ui_agreement.h"
#include "bytechange.h"
#include <QDebug>
Agreement::Agreement(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Agreement)
{
    ui->setupUi(this);
    connect(ui->head_edit,&QLineEdit::textChanged,this,&Agreement::head_edit_dispose);
    connect(ui->tailedit,&QLineEdit::textChanged,this,&Agreement::tail_edit_dispose);
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
    for(int i=0;i<data.head_byte;i++){
          head.append(data.tail[i]);
    }
    QString tail_str=hexToString(tail);

    ui->head_edit->setText(head_str);
    ui->tailedit->setText(tail_str);

    ui->databit->setCurrentIndex(data.databit);
    ui->checkmode->setCurrentIndex(data.check_mode);
}

Agree Agreement::read()          //ok读出
{

}


void Agreement::head_edit_dispose()
{
    QTextCursor mTextCursor = ui->head_edit->textCursor();
    if(mTextCursor.hasSelection())//清除选中
        mTextCursor.clearSelection();

    QString inputstring = ui->head_edit->toPlainText();
    qDebug()<<inputstring;
    char input;
    if(mTextCursor.positionInBlock()!=0)
        input = inputstring.at(mTextCursor.positionInBlock()-1).toLatin1();
    qDebug()<<input;
    if(input==' '||(input>='0'&&input<='9')||(input>='a'&&input<='f')||(input>='A'&&input<='F')){}
    else
    {
        //警告
        ui->head_edit->textCursor().deletePreviousChar();
    }
}
void Agreement::tail_edit_dispose()
{

}
