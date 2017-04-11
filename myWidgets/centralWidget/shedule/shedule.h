#ifndef SHEDULE_H
#define SHEDULE_H

#include <QWidget>
#include <QHBoxLayout>

#include "sheduleleftpanel.h"
#include "rightPanel/sheduleright.h"

#include "myClasses/mythread.h"
#include "myClasses/trackingdate.h"

class Shedule : public QWidget
{
    Q_OBJECT
public:
    Shedule(QWidget *parent = 0);
    ~Shedule();

    QHBoxLayout *pLayout;

    SheduleLeftPanel *pLeftWidget;
    SheduleRight *pRightWidget;

    unsigned int the_number_of_classes_in_parallel[11] ; //количестов классов в параллели

private:
    TrackingDate *trackingDate;
    myThread *thread;

    void checkDirsAndFiles(); //проверка на существование каталогов
    void checkDirsAndFilesFunc(QString local_or_share, QString dir_name);   // функция для функции checkDirsAndFiles()
    void checkDirsAndFilesFunc2(QString local_file, QString src_file);      // функция для функции checkDirsAndFiles()

signals:

public slots:
    void slotSheduleLeftPanelItemClick(QTreeWidgetItem*, int);
    void slotChangedDay(int day);
};

#endif // SHEDULE_H
