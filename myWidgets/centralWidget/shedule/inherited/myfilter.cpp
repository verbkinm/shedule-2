#include "myfilter.h"
#include <QDebug>
#include <QEvent>

MyFilter::MyFilter(QObject *parent) : QObject(parent)
{

}
bool MyFilter::eventFilter(QObject *, QEvent *e)
{
//    if(e->type() == QEvent::MouseButtonPress){
        qDebug() << e->type();
//        return true;
//    }
    return false;
}
