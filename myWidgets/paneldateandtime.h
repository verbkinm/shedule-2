#ifndef PANELDATEANDTIME_H
#define PANELDATEANDTIME_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QDateTime>


class PanelDateAndTime : public QWidget
{
    Q_OBJECT
public:
    PanelDateAndTime(QWidget *parent = 0);

    void setFontSize(int size);
    virtual void paintEvent(QPaintEvent * );


private:
    QLabel *pLabelTime, *pLabelDate;
    QString date,time;
    QTimer* pTimer;
    QFont* pFont;

    bool event(QEvent *event);

signals:
    void signalClick();

public slots:
    void slotSetCurrentDateAndTime();
};

#endif // PANELDATEANDTIME_H
