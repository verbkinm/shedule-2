#ifndef TRACKINGDATE_H
#define TRACKINGDATE_H

#include <QObject>
#include <QDate>

class TrackingDate : public QObject
{
    Q_OBJECT

    int day;
public:
    TrackingDate();
    void setDate();

public slots:
    void start();

signals:
    void signalChangedDay(int);
};

#endif // TRACKINGDATE_H
