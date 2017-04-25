#include "shedule.h"
#include "generalsettings.h"

#include <QDir>
#include <QDebug>

//CONSTRUKTOR
Shedule::Shedule(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("Shedule");

    checkDirsAndFiles();

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
    connect(trackingDate, SIGNAL(signalChangedDay(int)), this, SLOT(slotChangedDay(int)) );

    trackingDate->moveToThread(thread);
    thread->start();
}
//FUNCTIONS
void Shedule::checkDirsAndFiles()
{
//  local
    checkDirsAndFilesFunc("local", "архив");
    checkDirsAndFilesFunc("local", "на завтра");
    checkDirsAndFilesFunc("local", "на сегодня");
    checkDirsAndFilesFunc("local", "утвержденное");
//  share
    checkDirsAndFilesFunc("share", "архив");
    checkDirsAndFilesFunc("share", "на завтра");
    checkDirsAndFilesFunc("share", "на сегодня");
    checkDirsAndFilesFunc("share", "утвержденное");
//  README.txt and example files
    checkDirsAndFilesFunc2("README.txt", ":/examples/example_files/README.txt");
    checkDirsAndFilesFunc2("example_lessons.xml", ":/examples/example_files/example_lessons.xml");
    checkDirsAndFilesFunc2("local" + QString(PATH_SPLITER) + \
                           "расписание уроков" + QString(PATH_SPLITER) + \
                           "на сегодня" + QString(PATH_SPLITER) + \
                           "example_сегодня.xml",
                           ":/examples/example_files/example_сегодня.xml");
}
void Shedule::checkDirsAndFilesFunc(QString local_or_share, QString dir_name)
{
    QDir dir(QDir::currentPath() + PATH_SPLITER + \
                local_or_share + PATH_SPLITER + \
                "расписание уроков" + PATH_SPLITER + \
                dir_name);

    if(!dir.mkpath(dir.path()) ){
        printf("can't make dir %s\n", qPrintable(dir.path()) );
        exit(5);
    }
}
void Shedule::checkDirsAndFilesFunc2(QString local_file, QString src_file)
{
    QFile file(QDir::currentPath() + PATH_SPLITER + local_file);
    if(!file.open(QIODevice::WriteOnly)){
        printf("can't make file %s\n", qPrintable(QFileInfo(file).absolutePath()) );
        exit(5);
    }

    QFile example(src_file);
    example.open(QIODevice::ReadOnly);
    file.write(example.readAll() );
    file.close();
    example.close();
}

//SLOTS
void Shedule::slotSheduleLeftPanelItemClick(QTreeWidgetItem *item, int column)
{
    QString str     = "\0";
    QString lesson  = "\0";
    QString teacher = "\0";

    if(item->text(column) != TEXT_ROOT_LIST){
        if(item->parent()->text(column) != TEXT_ROOT_LIST){
            lesson = item->parent()->text(column);
            teacher = item->text(column);
        }
        else
            lesson = item->text(column);
    }
    else
        str = TEXT_SHEDULE_DEFAULT;

    QString buffLesson = lesson;
    QString buffTeacher= teacher;
    while( (buffLesson.length() + buffTeacher.length()) > STRING_LENGHT_SHEDULE_RIGHT_HEADER){
        if(buffLesson.length() > buffTeacher.length())
            buffLesson = buffLesson.mid(0, buffLesson.length() - 3) + "~:\0";
        if(buffLesson.length() < buffTeacher.length())
            buffTeacher = buffTeacher.mid(0, buffTeacher.length() - 3) + "~:\0";
    }

    str = buffLesson + " " + buffTeacher;

    pRightWidget->setHeaderText(str, lesson, teacher);
}
void Shedule::slotChangedDay(int day)
{
    qDebug() << "slot change day";

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
