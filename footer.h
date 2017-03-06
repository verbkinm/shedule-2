#ifndef FOOTER_H
#define FOOTER_H

#include <QWidget>
#include <QHBoxLayout>

#include "myWidgets/pushbutton.h"
#include "myWidgets/paneldateandtime.h"

class Footer : public QWidget
{
    Q_OBJECT
public:
    Footer(QWidget *parent = 0);
    ~Footer();

    void applySize();
    void disableButtonCurrentWidget(QObject *activeWidget);

private:
    int length;
    float currentSize;
    QHBoxLayout* pLayout;
    PushButton* buttons[4]; //*pHome, *pHelp, extra buttons;
    PanelDateAndTime* panelDateAndTime;
//    bool calendarView;

    void paintEvent(QPaintEvent * );

signals:
    void signalPushShedule();
    void signalPushNews();
    void signalPushHome();
    void signalPushDateAndTime();
    void signalPushHelp();

public slots:
    void slotStyleApply();
    void slotInDevelopment();
};

#endif // FOOTER_H
