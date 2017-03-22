#include "mylineedit.h"

#include <QDebug>
#include <QEvent>

MyLineEdit::MyLineEdit()
{
    setFocusPolicy(Qt::NoFocus);
}
void MyLineEdit::mousePressEvent(QMouseEvent*)
{
    setSelection(0,0);
}
void MyLineEdit::mouseReleaseEvent(QMouseEvent*)
{
    setSelection(0,0);
}
void MyLineEdit::mouseMoveEvent(QMouseEvent*)
{
    setSelection(0,0);
}
void MyLineEdit::mouseDoubleClickEvent(QMouseEvent*)
{
     setSelection(0,0);
}

bool MyLineEdit::event(QEvent *event)
{
    return QLineEdit::event(event);
}
