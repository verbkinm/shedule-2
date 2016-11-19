#include "shedule.h"

Shedule::Shedule(QWidget *parent) : QWidget(parent)
{
    pLayout         = new QHBoxLayout;
    pLayout->setSpacing(0);
    pLayout->setMargin(0);

    pLeftWidget     = new SheduleLeftPanel(this);
    pRightWidget    = new SheduleRight;

    pLayout->addWidget(pLeftWidget);
    pLayout->addWidget(pRightWidget);

    this->setLayout(pLayout);
}


