#include "sheduleright.h"
#include <QStyleOption>
#include <QPainter>

SheduleRight::SheduleRight(QWidget *parent) : QWidget(parent)
{

}
void SheduleRight::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
