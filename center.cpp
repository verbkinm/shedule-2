#include "center.h"
#include "widget.h"

#include <QStyleOption>
#include <QPainter>
#include <QMessageBox>

//CONSTRUKTOR
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
    connect(pHome, SIGNAL(signalLabel_1_Click()), SLOT(slotInDevelopment()) );
    connect(pHome, SIGNAL(signalLabel_2_Click()), SLOT(slotInDevelopment()) );
}
//FUNCTIONS
void Center::disableButtonCurrentWidget(QObject *activeWidget)
{
    Widget *widget = qobject_cast<Widget*>(parent());
    if(widget != 0)
        widget->footer->disableButtonCurrentWidget(activeWidget);
}
//SLOTS
void Center::slotInDevelopment()
{
    QMessageBox msgBox;
    msgBox.setWindowFlags(Qt::FramelessWindowHint);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("В разработке!");
    msgBox.exec();
}
void Center::slotViewHome()
{
    for(int i = 0; i < pLayout->count(); i++)
        pLayout->itemAt(i)->widget()->hide();
    pHome->setVisible(true);
    activeWidget = pHome;
    disableButtonCurrentWidget(activeWidget);
}
void Center::slotViewCalendar()
{
    for(int i = 0; i < pLayout->count(); i++)
        pLayout->itemAt(i)->widget()->hide();
    pCalendar->setVisible(true);
    activeWidget = pCalendar;
    disableButtonCurrentWidget(activeWidget);
}
void Center::slotViewShedule()
{
    for(int i = 0; i < pLayout->count(); i++)
        pLayout->itemAt(i)->widget()->hide();
    pShedule->setVisible(true);
    activeWidget = pShedule;
    disableButtonCurrentWidget(activeWidget);
}
//EVENTS
void Center::paintEvent(QPaintEvent * )
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
//DESTRUKTOR
Center::~Center()
{

}
