#ifndef AGREEMENT_H
#define AGREEMENT_H

#include <QWidget>
#include <QRegExp>
typedef struct
{
    uint8_t head[4];
    uint8_t databit;
    uint8_t tail[4];
    uint8_t head_byte;
    uint8_t tail_byte;
    uint8_t check_mode;
}Agree;
namespace Ui {
class Agreement;
}

class Agreement : public QWidget
{
    Q_OBJECT

public:
    explicit Agreement(QWidget *parent=0);
    ~Agreement();
    void write(Agree data);
    Agree read(void);

private:
    Ui::Agreement *ui;
};

#endif // AGREEMENT_H
