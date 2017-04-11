#ifndef MYTOUCHSCREEN_H
#define MYTOUCHSCREEN_H

#include <QWidget>

class MyTouchScreen : public QWidget
{
    Q_OBJECT
private:
    int startX, stopX;
    int startY, stopY;
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
//    virtual void mouseDoubleClickEvent(QMouseEvent*);

    bool event(QEvent *event);
public:
    MyTouchScreen(QWidget *parent = 0);

signals:
    void signalChangeX(int);
    void signalChangeY(int);

public slots:
};

#endif // MYTOUCHSCREEN_H
