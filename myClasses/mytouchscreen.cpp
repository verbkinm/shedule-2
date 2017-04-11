#include "mytouchscreen.h"

#include <QStyleOption>
#include <QPainter>
#include <QEvent>
#include <QDebug>

MyTouchScreen::MyTouchScreen(QWidget *parent) : QWidget(parent)
{
//    QPalette pal;
//    pal.setColor(QPalette::Background, Qt::red);
//    this->setPalette(pal);
//    this->setAutoFillBackground(true);
    startY = stopY = startX = stopX = -1;
}
//EVENTS
void MyTouchScreen::mousePressEvent(QMouseEvent*)
{
    startX = QCursor::pos().x();
    startY = QCursor::pos().y();
}
void MyTouchScreen::mouseMoveEvent(QMouseEvent*)
{
    stopX = QCursor::pos().x();
    stopY = QCursor::pos().y();

//POS X
    if( (startX + 5) < stopX){
        emit signalChangeX(-1);
        startX = stopX  = QCursor::pos().x();
    }
    if( (startX - 5) > stopX){
        emit signalChangeX(1);
        startX = stopX  = QCursor::pos().x();
    }
//POS Y
    if( (startY + 5) < stopY){
        emit signalChangeY(-1);
        startY = stopX  = QCursor::pos().y();
    }
    if( (startY - 5) > stopY){
        emit signalChangeY(1);
        startY = stopY = QCursor::pos().y();
    }
}
void MyTouchScreen::mouseReleaseEvent(QMouseEvent *)
{
    startY = stopY = startX = stopX = -1;
}

bool MyTouchScreen::event(QEvent *event)
{
    return QWidget::event(event);
}
