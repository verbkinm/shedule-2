#include "center.h"

#include <QStyleOption>
#include <QPainter>

Center::Center(QWidget *parent) : QWidget(parent)
{
    desktop = new Desktop;

    pLayout = new QVBoxLayout;
    pLayout->setContentsMargins(0,0,0,0);
    pLayout->addWidget(desktop);

    this->setLayout(pLayout);

//    desktop->setSize();
}
void Center::applySize(void)
{

}
void Center::paintEvent(QPaintEvent * )
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
Center::~Center()
{

}
