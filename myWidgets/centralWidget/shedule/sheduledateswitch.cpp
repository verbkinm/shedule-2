#include "sheduledateswitch.h"
#include "generalsettings.h"

#include <QDate>
#include <QColor>
#include <QPalette>
#include <QStyleOption>
#include <QPainter>

//CONSTRUKTOR
SheduleDateSwitch::SheduleDateSwitch(QWidget *parent) : QWidget(parent)
{
    QSize size(SHEDULE_DATE_SWITCH_BUTTON_SIZE,SHEDULE_DATE_SWITCH_BUTTON_SIZE);
    pPreviousDay= new PushButton(":/img/previos_button", ":/img/previos_button_push", size);
    pNextDay    = new PushButton(":/img/next_button", ":/img/next_button_push", size);

    pDate       = new MyLineEdit;
    pDate->setText(QDate::currentDate().toString("dd-MM-yyyy"));
    pDate->setAlignment(Qt::AlignCenter);
    pDate->setReadOnly(true);

    pLayout     = new QHBoxLayout;
    pLayout->addWidget(pPreviousDay);
    pLayout->addWidget(pDate);
    pLayout->addWidget(pNextDay);

    this->setLayout(pLayout);

    connect(pPreviousDay, SIGNAL(signalClick()), SIGNAL(signalPreviosDay())  );
    connect(pNextDay    , SIGNAL(signalClick()), SIGNAL(signalNextDay())     );
//    this->setFixedWidth(SHEDULE_DATE_SIZE_WIDTH);
}
//FUNCTIONS

//SLOTS

//EVENTS
void SheduleDateSwitch::paintEvent(QPaintEvent * )
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
//DESTRUKTOR
