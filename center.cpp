#include "center.h"
#include "widget.h"

#include <QStyleOption>
#include <QPainter>

Center::Center(QWidget *parent) : QWidget(parent)
{
    pParent = parent;

    pHome = new Desktop;
    activeWidget = pHome;

    pLayout = new QVBoxLayout;
    pLayout->setContentsMargins(0,0,0,0);

    pLayout->addWidget(pHome);

    this->setLayout(pLayout);

    connect(pHome, SIGNAL(signalLabel_0_Click()), SLOT(slotViewShedule()) );
    disableButtonCurrentWidget(activeWidget);
}
void Center::disableButtonCurrentWidget(QObject *activeWidget)
{
    Widget *widget = qobject_cast<Widget*>(pParent);
    if(widget != 0)
        widget->footer->disableButtonCurrentWidget(activeWidget);
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
    delete activeWidget;
    pHome = new Desktop;
    activeWidget = pHome;
    pLayout->addWidget(pHome);
    pHome->showMaximized();
    pHome->setUnits();
    connect(pHome, SIGNAL(signalLabel_0_Click()), SLOT(slotViewShedule()) );
    disableButtonCurrentWidget(activeWidget);
}
void Center::slotViewCalendar()
{
    delete activeWidget;
    pCalendar = new Calendar;
    activeWidget = pCalendar;
    pLayout->addWidget(pCalendar);
    disableButtonCurrentWidget(activeWidget);
}
void Center::slotViewShedule()
{
    delete activeWidget;
    pShedule = new Shedule;
    activeWidget = pShedule;
    pLayout->addWidget(pShedule);
    disableButtonCurrentWidget(activeWidget);
}

Center::~Center()
{

}
