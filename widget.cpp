#include "widget.h"

#include <QDesktopWidget>

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


    header->setFixedHeight(heightDesktop / 100 * 20);
    footer->setFixedHeight(heightDesktop / 100 * 20);

    center->setMaximumHeight(heightDesktop - (header->height() + footer->height()) );

    pL->addWidget(header);
    pL->addWidget(center);
    pL->addWidget(footer);

    header->applySize();
    footer->applySize();

    this->setLayout(pL);
}
Widget::~Widget()
{

}
