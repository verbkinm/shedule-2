#include "sheduleright.h"

#include <QStyleOption>
#include <QEvent>
#include <QDebug>
#include <QPainter>

static int resized = 0;

SheduleRight::SheduleRight(QWidget *parent) : QWidget(parent)
{
    pLayout = new QVBoxLayout;
    pLayout->setMargin(0);
    pLayout->setContentsMargins(0,0,0,0);
    pLayout->setSpacing(0);

    pHeader = new QLabel("Расписание");
    QFont *pFont = new QFont(pHeader->font());
    pFont->setPixelSize(35);
    pFont->setBold(true);
    pHeader->setFont(*pFont);
    pHeader->setAlignment(Qt::AlignCenter);
    pHeader->setFixedHeight(80);

    pSheduleRightTableWidget = new SheduleRightTableWidget;

    pLayout->addWidget(pHeader);
    pLayout->addWidget(pSheduleRightTableWidget);

    this->setLayout(pLayout);
}
void SheduleRight::setHeaderText(QString str){
    pHeader->setText(str);
}
void SheduleRight::setUnits()
{
    qDebug() << this->size();
    this->setFixedSize(this->size());
}

bool SheduleRight::event(QEvent *event)
{
//    qDebug() << event->type();
    if(this->isVisible() && event->type() == QEvent::Resize && resized < 1){
        setUnits();
        resized = 1;
    }

}

void SheduleRight::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}