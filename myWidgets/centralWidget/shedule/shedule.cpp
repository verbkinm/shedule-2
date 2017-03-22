#include "shedule.h"
#include "generalsettings.h"

#include <QDebug>

//CONSTRUKTOR
Shedule::Shedule(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("Shedule");

    pLayout         = new QHBoxLayout;
    pLayout->setSpacing(0);
    pLayout->setMargin(0);

    pLeftWidget     = new SheduleLeftPanel;
    pRightWidget    = new SheduleRight(this);

    pLayout->addWidget(pLeftWidget);
    pLayout->addWidget(pRightWidget);

    this->setLayout(pLayout);
    this->setObjectName(OBJECT_NAME_SHEDULE);

    connect(pLeftWidget, SIGNAL(signalItemClick(QTreeWidgetItem*, int)), SLOT(slotSheduleLeftPanelItemClick(QTreeWidgetItem*, int)) );

//    for (int i = 0; i < 11; ++i) {
//        qDebug() << i+1 << the_number_of_classes_in_parallel[i];
//    }
}
//SLOTS
void Shedule::slotSheduleLeftPanelItemClick(QTreeWidgetItem *item, int column)
{
    QString str     = "\0";
    QString lesson  = "\0";
    QString teacher = "\0";

    if(item->text(column) != TEXT_ROOT_LIST){
        if(item->parent()->text(column) != TEXT_ROOT_LIST)
            lesson = item->parent()->text(column);
        teacher = item->text(column);
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
//DECONSTRUKTOR
Shedule::~Shedule()
{
    qDebug() << "shedule destruktor";
}
