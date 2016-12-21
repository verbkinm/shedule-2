#include "center.h"

#include <QStyleOption>
#include <QPainter>

Center::Center(QWidget *parent) : QWidget(parent)
{
    pHome = new Desktop;


    pCalendar = new Calendar;
    pCalendar->setVisible(false);

    pShedule = new Shedule;
    pShedule->setVisible(false);

    pLayout = new QVBoxLayout;
    pLayout->setContentsMargins(0,0,0,0);
    pLayout->addWidget(pHome);
    pLayout->addWidget(pCalendar);
    pLayout->addWidget(pShedule);

    this->setLayout(pLayout);

    connect(pHome, SIGNAL(signalLabel_0_Click()), SLOT(slotViewShedule()) );
}
void Center::paintEvent(QPaintEvent * )
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void Center::slotViewHome()
{
    for(int i = 0; i < pLayout->count(); i++)
        pLayout->itemAt(i)->widget()->hide();
    pHome->setVisible(true);
}
void Center::slotViewCalendar()
{
    for(int i = 0; i < pLayout->count(); i++)
        pLayout->itemAt(i)->widget()->hide();
    pCalendar->setVisible(true);
}
void Center::slotViewShedule()
{
    for(int i = 0; i < pLayout->count(); i++)
        pLayout->itemAt(i)->widget()->hide();
    pShedule->setVisible(true);
}

Center::~Center()
{

}
