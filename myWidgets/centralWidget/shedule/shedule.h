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

signals:

public slots:
};

#endif // SHEDULE_H
