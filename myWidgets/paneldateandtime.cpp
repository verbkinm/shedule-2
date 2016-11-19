#include "paneldateandtime.h"

#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include <QFont>
#include <QEvent>
//#include <QDebug>

PanelDateAndTime::PanelDateAndTime(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout * pLayout = new QVBoxLayout;

    time = QDateTime::currentDateTime().time().toString("hh:mm:ss");
    date = QDateTime::currentDateTime().date().toString("dd:MM:yyyy");

    pLabelTime = new QLabel(time);
    pLabelTime->setAlignment(Qt::AlignCenter);
    pLabelDate = new QLabel(date);
    pLabelDate->setAlignment(Qt::AlignCenter);

    pLayout->addWidget(pLabelTime);
    pLayout->addWidget(pLabelDate);

    this->setLayout(pLayout);

    pTimer = new QTimer;
    pTimer->start(1000);

    pFont = new QFont(pLabelTime->font());

    connect(pTimer,     SIGNAL(timeout()),      SLOT(slotSetCurrentDateAndTime()) );
}
void PanelDateAndTime::setFontSize(int size)
{
    pFont->setPixelSize(size);
    pFont->setBold(true);
    pLabelTime->setFont(*pFont);
    pLabelDate->setFont(*pFont);
}

void PanelDateAndTime::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void PanelDateAndTime::slotSetCurrentDateAndTime()
{
    time = QDateTime::currentDateTime().time().toString("hh:mm:ss");
    date = QDateTime::currentDateTime().date().toString("dd:MM:yyyy");

    pLabelTime->setText(time);
    pLabelDate->setText(date);
}
bool PanelDateAndTime::event(QEvent *event)
{
  if(event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick )
      emit signalClick();
  return QWidget::event(event);
}

