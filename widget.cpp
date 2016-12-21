#include "widget.h"

#include <QDesktopWidget>
//#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QDesktopWidget desktop;
    int heightDesktop = desktop.screenGeometry().height();

    QVBoxLayout* pL = new QVBoxLayout;
    pL->setMargin(0);
    pL->setContentsMargins(0,0,0,0);
    pL->setSpacing(0);

    header = new Header;
    center = new Center;
    footer = new Footer;


    header->setFixedHeight(heightDesktop / 100 * 15);
    footer->setFixedHeight(heightDesktop / 100 * 15);

    center->setMaximumHeight(heightDesktop - (header->height() + footer->height()) );

    pL->addWidget(header);
    pL->addWidget(center);
    pL->addWidget(footer);

    header->applySize();
    footer->applySize();

    this->setLayout(pL);

    connect(footer, SIGNAL(signalPushHome()), SLOT(slotVeiwHome()) ); // home
    connect(footer, SIGNAL(signalPushDateAndTime()), SLOT(slotVeiwCalendar()) ); // calendar
    connect(footer, SIGNAL(signalPushShedule()), SLOT(slotVeiwShedule()) ); // shedule
}
void Widget::slotVeiwHome()
{center->slotViewHome();}
void Widget::slotVeiwCalendar()
{center->slotViewCalendar();}
void Widget::slotVeiwShedule()
{center->slotViewShedule();}
Widget::~Widget()
{

}
