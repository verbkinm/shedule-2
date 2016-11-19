#include "sheduleleftpanel.h"

#include <QStyleOption>
#include <QPainter>
#include <QEvent>
#include <QDebug>

static int resized = 0;

SheduleLeftPanel::SheduleLeftPanel(QWidget *parent) : QWidget(parent)
{
    pParent = parent;
    pLayout = new QVBoxLayout;
    pListWidget = new QListWidget;

    this->setContentsMargins(0,0,0,0);
    this->setLayout(pLayout);
}
void SheduleLeftPanel::setUnits()
{
    this->setFixedSize(float(pParent->width()) / 100 * 25, pParent->height());
    QStringList list;
    list << "> Предметы" << "> Кабинеты";
    pListWidget->addItems(list);

    pLayout->addWidget(pListWidget);

}
void SheduleLeftPanel::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
bool SheduleLeftPanel::event(QEvent *event)
{
    qDebug() << event->type();
    if(event->type() == QEvent::Resize && resized < 1){
        this->setUnits();
        resized = 1;
    }
    return QWidget::event(event);
}

