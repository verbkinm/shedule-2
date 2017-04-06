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


    //отслеживание за сменой суток(числа месяца)
    trackingDate = new TrackingDate;
    trackingDate->setDate();
    thread = new myThread;

    connect(thread, SIGNAL(started()), trackingDate, SLOT(start()) );

    trackingDate->moveToThread(thread);
    thread->start();
    connect(trackingDate, SIGNAL(signalChangedDay(int)), this, SLOT(slotChangedDay(int)) );
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
void Shedule::slotChangedDay(int day)
{
    QFile shareToday(SHARE_FILE_MAIN_SHEDULE_TODAY);
    QFile shareYesterday(SHARE_FILE_MAIN_SHEDULE_YESTERDAY);

    QFile localToday(LOCAL_FILE_MAIN_SHEDULE_TODAY);
    QFile localYestaerday(LOCAL_FILE_MAIN_SHEDULE_YESTERDAY);

    //LOCAL_FILE
    if(!localYestaerday.remove())
        printf("error remove file %s\n", qPrintable(LOCAL_FILE_MAIN_SHEDULE_YESTERDAY));
    else
        printf("file removed %s\n", qPrintable(LOCAL_FILE_MAIN_SHEDULE_YESTERDAY));
    if(!localToday.remove())
        printf("error remove file %s\n", qPrintable(LOCAL_FILE_MAIN_SHEDULE_TODAY));
    else
        printf("file removed %s\n", qPrintable(LOCAL_FILE_MAIN_SHEDULE_TODAY));
    //SHARE_FILE
    if(!shareToday.remove())
        printf("error remove file %s\n", qPrintable(SHARE_FILE_MAIN_SHEDULE_TODAY));
    else
        printf("file removed %s\n", qPrintable(SHARE_FILE_MAIN_SHEDULE_TODAY));
    if(shareYesterday.open(QIODevice::ReadOnly)){
        QFile newShareToday(SHARE_FILE_MAIN_SHEDULE_TODAY);
        if(newShareToday.open(QIODevice::WriteOnly))
            newShareToday.write(shareYesterday.readAll());

        newShareToday.close();
        shareYesterday.close();
        if(!shareYesterday.remove())
            printf("error remove file %s\n", qPrintable(SHARE_FILE_MAIN_SHEDULE_YESTERDAY));
        else
            printf("file removed %s\n", qPrintable(SHARE_FILE_MAIN_SHEDULE_YESTERDAY));
    }

}

//DECONSTRUKTOR
Shedule::~Shedule()
{
    qDebug() << "shedule destruktor";
}
