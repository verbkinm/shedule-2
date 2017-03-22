#ifndef SHEDULE_H
#define SHEDULE_H

#include <QWidget>
#include <QHBoxLayout>

#include "sheduleleftpanel.h"
#include "sheduleright.h"

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

signals:

public slots:
    void slotSheduleLeftPanelItemClick(QTreeWidgetItem*, int);
};

#endif // SHEDULE_H
