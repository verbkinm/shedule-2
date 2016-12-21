#ifndef SHEDULE_H
#define SHEDULE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QListWidget>

#include "sheduleleftpanel.h"
#include "sheduleright.h"

class Shedule : public QWidget
{
    Q_OBJECT
public:
    explicit Shedule(QWidget *parent = 0);

    QHBoxLayout *pLayout;

    SheduleLeftPanel *pLeftWidget;
    SheduleRight *pRightWidget;

private:
    bool event(QEvent *event);
signals:

public slots:
    void slotSheduleLeftPanelItemClick(QTreeWidgetItem*);
};

#endif // SHEDULE_H
