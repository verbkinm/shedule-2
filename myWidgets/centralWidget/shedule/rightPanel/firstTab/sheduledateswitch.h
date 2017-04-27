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
    QGridLayout *pLayout;
    PushButton *pPreviousDay, *pNextDay;
    MyLineEdit *pDate;

    QLabel *leftArrow, *rightArrow;

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

    void slotSetLeftArrow(int); // 0 - south; 1 - sw; 2 - west; 3 - nw;
    void slotSetRightArrow(int); // 0 - nord; 1 - ne; 2 - east; 3 - se;
};

#endif // SHEDULEDATESWITCH_H
