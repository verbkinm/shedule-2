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

private:
    int length;
    float currentSize;
    QHBoxLayout* pLayout;
    PushButton* buttons[4]; //*pHome, *pHelp, extra buttons;
    PanelDateAndTime* panelDateAndTime;

    void paintEvent(QPaintEvent * );

signals:
    void signalPushHome();
    void signalPushHelp();
    void signalPushShedule();
    void signalPushNews();

public slots:
    void slotStyleApply();
};

#endif // FOOTER_H
