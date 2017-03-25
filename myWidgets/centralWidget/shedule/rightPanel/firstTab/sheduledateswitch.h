#ifndef SHEDULEDATESWITCH_H
#define SHEDULEDATESWITCH_H

#include <QWidget>
#include <QHBoxLayout>
#include "../../../../pushbutton.h"
#include "../../inherited/mylineedit.h"
#include <QLineEdit>

class SheduleDateSwitch : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout *pLayout;
    PushButton *pPreviousDay, *pNextDay;
    MyLineEdit *pDate;

    void setButtonsState();

    void paintEvent(QPaintEvent * );

public:
    SheduleDateSwitch(QWidget *parent = 0);
    ~SheduleDateSwitch();

    void setSheduleDateSwitch(QString);

signals:
    void signalPreviosDay();
    void signalNextDay();

public slots:
    void slotSetDateSheduleDateSwitch();
};

#endif // SHEDULEDATESWITCH_H
