#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myserial = NULL;
    mytcp    = new myTCP(ui->portsetweight);
    memset(&sendsta,false,sizeof(sendsta));
    memset(&receivesta,false,sizeof(receivesta));

    ui->sendtimeset->setValidator(new QIntValidator(1,50000,this));
    portopen_en=false;
    Timer0_Init(1000);
    MesStatusBar();
    connect(ui->send_edit,&QTextEdit::textChanged,this,&MainWindow::sendedit_dispose);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//初始化
void MainWindow::Timer0_Init(uint16_t time)
{
    myTime_0 = new QTimer();
    myTime_0->stop();
    myTime_0->setInterval(time);
    connect(myTime_0,SIGNAL(timeout()),this,SLOT(time0_task(void)));
    myTime_0->start();

}

void MainWindow::MesStatusBar()
{
    QLabel *l = new QLabel(tr("Read:"));
    QLabel *mid = new QLabel(tr("   "));
    QLabel *e = new QLabel(tr("Send:"));
    label_rec = new QLabel(tr("0"));
    label_send = new QLabel(tr("0"));
    ui->statusBar->addWidget(l);
    ui->statusBar->addWidget(label_rec);
    ui->statusBar->addWidget(mid);
    ui->statusBar->addWidget(e);
    ui->statusBar->addWidget(label_send);
}
//端口检测
void MainWindow::time0_task(void)
{
    QStringList port_num;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        port_num += info.portName()+"  "+info.description();  
    }
    if(port_num.size()!=serialport_list.size()&&portopen_en==false)
    {
        QStringList same;
        QStringList diff_now,diff_last;
        //比较出相同项及增加项
        for(uint8_t i=0;i<port_num.size();i++)
        {
            bool flag=false;
            for(uint8_t j=0;j<serialport_list.size();j++)
            {
                if(port_num.value(i)==serialport_list.value(j))
                {
                    same<<port_num.value(i);
                    flag=true;
                    break;
                }
            }
            if(flag==false)
            {
                diff_now<<port_num.value(i);
            }
        }
        //比较出减少项并删除
        for(uint8_t i=0;i<serialport_list.size();i++)
        {
            bool flag=false;
            for(uint8_t j=0;j<same.size();j++)
            {
                if(serialport_list.value(i)==same.value(j))
                {
                   flag=true;
                   break;
                }
            }
            if(flag==false)
                ui->portchoose->removeItem(ui->portchoose->findText(serialport_list.value(i)));
        }
        ui->portchoose->addItems(diff_now);
        serialport_list=port_num;
        qDebug()<<port_num;
    }
}
//端口选择
void MainWindow::on_portchoose_currentIndexChanged(int index)
{
    if(portopen_en==false)
    {
        qDebug()<<index;
        delete myserial;
        delete mytcp;

        if(index==0)
        {
            mytcp = new myTCP(ui->portsetweight); myserial=NULL;
        }
        else
        {
            QString name =ui->portchoose->currentText();
            myserial = new mySerial(ui->portsetweight,name.left(5)); mytcp=NULL;
            connect(myserial,&mySerial::serial_readdata,this,&MainWindow::data_dispose);
            connect(ui->senddatabtn,&QPushButton::clicked,this,&MainWindow::send_data_serial);
            connect(myserial,&mySerial::serial_status,this,&MainWindow::changeportopen_en);
        }

    }
}
//数据处理及发送
void MainWindow::sendedit_dispose()
{
    if(sendsta.hexsend==true)
    {
        QTextCursor mTextCursor = ui->send_edit->textCursor();
        if(mTextCursor.hasSelection())//清除选中
            mTextCursor.clearSelection();

        QString inputstring = ui->send_edit->toPlainText();
        qDebug()<<inputstring;
        char input;
        if(mTextCursor.positionInBlock()!=0)
            input = inputstring.at(mTextCursor.positionInBlock()-1).toLatin1();
        qDebug()<<input;
        if(input==' '||(input>='0'&&input<='9')||(input>='a'&&input<='f')||(input>='A'&&input<='F')){}
        else
        {
            //警告
            ui->send_edit->textCursor().deletePreviousChar();
        }

    }
}
void MainWindow::data_dispose(QByteArray str)
{
    readdata_num.append(str);

    QString num = QString::number(readdata_num.size());
    label_rec->setText(num);

    edit_show(str,0);
}
void MainWindow::send_data_serial()
{
    QByteArray senddata;
    if(portopen_en==true)
    {
        QString str;
        str = ui->send_edit->toPlainText();
        if(sendsta.hexsend==false)
        {
            senddata=str.toLatin1();
        }
        else
        {
            senddata = QString2Hex(str);
        }
         myserial->send_data(senddata);
        if(sendsta.sendshow==true)
        {
            edit_show(senddata,1);
        }
    }
    senddata_num.append(senddata);
    QString num = QString::number(senddata_num.size());
    label_send->setText(num);
}
void MainWindow::send_data_tcp()
{
    if(portopen_en==true)
    {
        QString str;
        str = ui->send_edit->toPlainText();
        myserial->send_data(str.toLatin1());
    }
}
void MainWindow::edit_show(QByteArray byte_,uint8_t flag)
{
    QString show;
    QString str;
    qDebug()<<byte_;
    if(receivesta.timeshow==true)
    {
        QDateTime time = QDateTime::currentDateTime();
        show=time.toString("[hh:mm:ss.zzz] ");
    }
    if(sendsta.sendshow==true)
    {
        switch (flag) {
        case 0:{show.append("[收]：");}break;
        case 1:{show.append("[发]：");}break;
        default:break;
        }
    }
    if(receivesta.hexshow==false)
    {
        str = QString(byte_);
        show.append(str);
    }
    else
    {
        QString strshow =hexToString(byte_);
        show.append(strshow);
        qDebug()<<strshow;
    }
    ui->receive_edit->append(show);
}

//功能标志控制函数
void MainWindow::changeportopen_en(bool flag)
{
    portopen_en=flag;
}
void MainWindow::on_cleanrecivebtn_clicked()
{
    readdata_num.clear();

    QString num = QString::number(readdata_num.size());
    label_rec->setText(num);

    ui->receive_edit->clear();
}
void MainWindow::on_savebtn_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this,"选择目录","D:\\qtpractice",\
                                                         QFileDialog::ShowDirsOnly);
    qDebug()<<path;
    QDateTime time = QDateTime::currentDateTime();
    int time_int = time.toTime_t();
    QString filename = "/text_"+QString::number(time_int)+".txt";

    QFile fp;
    fp.setFileName(path+filename);
    fp.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&fp);
    out<<ui->receive_edit->toPlainText();
    fp.close();

    QString filename_ = "/byte_"+QString::number(time_int)+".dat";

    QFile fp_;
    fp_.setFileName(path+filename_);
    fp_.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QDataStream out_(&fp_);
    out_<<readdata_num;
    fp_.close();
}
void MainWindow::on_topweight_clicked(bool checked)
{
    if(checked==true)
    {
        this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint);
        this->show();
    }
    else
    {
        this->setWindowFlags(this->windowFlags()&~Qt::WindowStaysOnTopHint);
        this->show();
    }
}
void MainWindow::on_Hexshow_clicked(bool checked)
{
    receivesta.hexshow=checked;
}
void MainWindow::on_Hexsend_clicked(bool checked)
{
    sendsta.hexsend=checked;
}
void MainWindow::on_RevicceToFile_clicked(bool checked)
{
    receivesta.filerecive=checked;
}
void MainWindow::on_sendOntime_clicked(bool checked)
{
    sendsta.timersend=checked;
}
void MainWindow::on_timeshow_clicked(bool checked)
{
    receivesta.timeshow=checked;
}
void MainWindow::on_addlineend_clicked(bool checked)
{
    sendsta.entersend=checked;
}
void MainWindow::on_addverify_clicked(bool checked)
{
    sendsta.checksend=checked;
}
void MainWindow::on_sendshow_clicked(bool checked)
{
    sendsta.sendshow=checked;
}
void MainWindow::on_openfilebtn_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"打开文件","D:\\qtpractice");
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray arry = file.readAll();
    ui->receive_edit->clear();
    file.close();

    if(receivesta.hexshow==false)
    {
        ui->receive_edit->append(arry);
    }
    else
    {
        QString strwrite;
        QString str = arry.toHex().data();
        str = str.toUpper();
        for(int i=0; i<str.length(); i+=2)
        {
            QString st = str.mid(i,2);
            strwrite += "0x";
            strwrite += st;
            strwrite += " ";
        }
        ui->receive_edit->append(strwrite);
    }
}

void MainWindow::on_cleansendbtn_clicked()
{
    ui->send_edit->clear();
    senddata_num.clear();

    QString num = QString::number(senddata_num.size());
    label_send->setText(num);
}


