#ifndef MAINSHEDULE_H
#define MAINSHEDULE_H

#include <QWidget>
#include <QGridLayout>

#include "shedulerighttablewidget.h"
#include "sheduledateswitch.h"

class MainShedule : public QWidget
{
    Q_OBJECT
private:
    SheduleRightTableWidget     *pSheduleRightTableWidget;
    SheduleDateSwitch           *pSheduleDateSwitch;
    QGridLayout                 *pLayout;

public:
    MainShedule(QWidget *parent = 0);

signals:

public slots:
    void slotSetDate(QString);
};

#endif // MAINSHEDULE_H
