#include "mainshedule.h"
#include "generalsettings.h"

#include <QScrollBar>

#include <QDebug>

//CONSTRUCTOR
MainShedule::MainShedule(QWidget *parent) : QWidget(parent)
{
    pLayout = new QGridLayout;

    pSheduleRightTableWidget = new SheduleRightTableWidget;
    pSheduleDateSwitch       = new SheduleDateSwitch;
//    pSheduleDateSwitch->setMaximumWidth(SHEDULE_DATE_SIZE_WIDTH);

    pLayout->addWidget(pSheduleRightTableWidget, 0,0);
//    pLayout->addWidget(pSheduleRightTableWidget->getHorizontalScroolBar(), 1,0);
    pLayout->addWidget(pSheduleDateSwitch, 2,0, Qt::AlignCenter);

    this->setLayout(pLayout);

    connect(pSheduleDateSwitch, SIGNAL(signalPreviosDay(QString)), pSheduleRightTableWidget, SLOT(slotrRecreateTables(QString)) );
    connect(pSheduleDateSwitch, SIGNAL(signalNextDay(QString)),    pSheduleRightTableWidget, SLOT(slotrRecreateTables(QString)) );
    connect(pSheduleRightTableWidget, SIGNAL(signalSetDateSheduleDateSwitch(QString)), SLOT(slotSetDate(QString)) );

    slotSetDate(pSheduleRightTableWidget->currentFile);
}
//FUNCTIONS
//SLOTS
void MainShedule::slotSetDate(QString date)
{
    pSheduleDateSwitch->setSheduleDateSwitch(date);
    pLayout->addWidget(pSheduleRightTableWidget->getHorizontalScroolBar(), 1,0);
}
//EVENTS
//DESTRUCTOR
