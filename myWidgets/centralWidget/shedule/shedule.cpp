#include "shedule.h"
#include "generalsettings.h"

#include <QDebug>

Shedule::Shedule(QWidget *parent) : QWidget(parent)
{
    pLayout         = new QHBoxLayout;
    pLayout->setSpacing(0);
    pLayout->setMargin(0);

    pLeftWidget     = new SheduleLeftPanel;
    pRightWidget    = new SheduleRight;

    pLayout->addWidget(pLeftWidget);
    pLayout->addWidget(pRightWidget);

    this->setLayout(pLayout);
    this->setObjectName(OBJECT_NAME_SHEDULE);

    connect(pLeftWidget, SIGNAL(signalItemClick(QTreeWidgetItem*)), SLOT(slotSheduleLeftPanelItemClick(QTreeWidgetItem*)) );
}

void Shedule::slotSheduleLeftPanelItemClick(QTreeWidgetItem *item)
{
    QString str     = "\0";
    QString lesson  = "\0";
    QString teacher = "\0";

    if(item->text(0) != TEXT_ROOT_LIST){
        if(item->parent()->text(0) != TEXT_ROOT_LIST)
            lesson = item->parent()->text(0);
        teacher = item->text(0);
    }
    else
        lesson = TEXT_SHEDULE_DEFAULT;

    while( (lesson.length() + teacher.length()) > STRING_LENGHT_SHEDULE_RIGHT_HEADER){
        if(lesson.length() > teacher.length())
            lesson = lesson.mid(0, lesson.length() - 3) + "~:\0";
        if(lesson.length() < teacher.length())
            teacher = teacher.mid(0, teacher.length() - 3) + "~:\0";
    }

    str = lesson + " " + teacher;
    pRightWidget->setHeaderText(str);
}
Shedule::~Shedule()
{
    qDebug() << "shedule destruktor";
}
