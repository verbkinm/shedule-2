#include "trackingdate.h"

#include <QThread>
#include <QDebug>

TrackingDate::TrackingDate()
{

}
void TrackingDate::start()
{
    qDebug() << "trackingday start";
    while(true) {
        QThread::sleep(1);
        if(day != QDate::currentDate().day()){
            day = QDate::currentDate().day();
            emit signalChangedDay(day);
        }
    }
}
void TrackingDate::setDate()
{
    day = QDate::currentDate().day();
}
