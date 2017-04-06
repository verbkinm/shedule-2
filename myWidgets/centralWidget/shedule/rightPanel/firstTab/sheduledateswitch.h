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

    QString previosFileName, nextFileName;

    void setButtonsState();
    bool checkDatePrevios(QString year, QString month, QString day);
    bool checkDateNext   (QString year, QString month, QString day);

    void paintEvent(QPaintEvent * );

public:
    SheduleDateSwitch(QWidget *parent = 0);
    ~SheduleDateSwitch();

    void setSheduleDateSwitchText(QString);

signals:
    void signalPreviosDay(QString fileName);
    void signalNextDay(QString fileName);

public slots:
    void slotPreviosDay();
    void slotNextDay();
};

#endif // SHEDULEDATESWITCH_H
