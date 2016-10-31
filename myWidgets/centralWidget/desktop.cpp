#include "desktop.h"

#include <QStyleOption>
#include <QPainter>
#include <QLabel>
#include <QDebug>

Desktop::Desktop(QWidget *parent) : QWidget(parent)
{
    pLayout = new QGridLayout;
    pLayout->setContentsMargins(50,100,50,100);
    pLayout->setSpacing(50);

    QString images[6];
    images[0] = ":/img/labelShedule";
    for(int i = 0; i < LABEL_COUNTS; i++)
        pLabelShedule[i] = new LabelWorkSpace(this->size(),images[i]);


    for(int i = 0, label = 0; i < 2; i++)
        for(int j = 0; j < 3; j++, label++)
            pLayout->addWidget(pLabelShedule[label],i,j);

    this->setLayout(pLayout);

//    if(this->isVisible()){
        for (int var = 0; var < LABEL_COUNTS; ++var)
            pLabelShedule[var]->setSize();
//    }
}
//void Desktop::setSize()
//{

//}

void Desktop::paintEvent(QPaintEvent * )
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
Desktop::~Desktop()
{

}
