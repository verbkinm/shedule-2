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

    QHBoxLayout *pLayout;

    SheduleLeftPanel *pLeftWidget;
    SheduleRight *pRightWidget;

private:

signals:

public slots:
    void slotSheduleLeftPanelItemClick(QTreeWidgetItem*);
};

#endif // SHEDULE_H
