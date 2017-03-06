#ifndef CENTER_H
#define CENTER_H

#include <QWidget>
#include <QVBoxLayout>

#include "myWidgets/centralWidget/desktop.h"
#include "myWidgets/centralWidget/calendar.h"
#include "myWidgets/centralWidget/shedule/shedule.h"

class Center : public QWidget
{
    Q_OBJECT
public:
    Center(QWidget *parent = 0);
    ~Center();

private:

    QVBoxLayout *pLayout;

    void paintEvent(QPaintEvent * );

    Desktop *pHome;
    Calendar *pCalendar;

    Shedule *pShedule;

    QObject *activeWidget;
    void disableButtonCurrentWidget(QObject *activeWidget);

signals:

public slots:
    void slotViewHome();
    void slotViewCalendar();
    void slotViewShedule();
};

#endif // CENTER_H
