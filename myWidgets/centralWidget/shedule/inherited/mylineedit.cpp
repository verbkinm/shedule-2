#include "mylineedit.h"

#include <QDebug>
#include <QEvent>

//CONSTRUKTOR
MyLineEdit::MyLineEdit(QWidget *p) : QLineEdit( p )
{
    setFocusPolicy(Qt::NoFocus);
    if( p ){
        QPalette pal = palette();
        pal.setColor( backgroundRole(), p->palette().color( p->backgroundRole() ) );
        setPalette( pal );
    }
    connect( this, SIGNAL(textChanged(QString)), this, SLOT(slotResizeByContents()) );
}
//FUNCTIONS
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
QSize MyLineEdit::sizeHint()
{
    QRect r = fontMetrics().boundingRect( text() );
    int lm, rm, tm, bm;
    getTextMargins( &lm, &tm, &rm, &bm );
    return QSize( r.width() + lm + rm + 20, QLineEdit::sizeHint().height() );
}
QSize MyLineEdit::minimumSizeHint()
{
    return sizeHint();
}
//SLOTS
void MyLineEdit::slotResizeByContents()
{
    setFixedWidth( sizeHint().width() );
    if( QWidget* p = parentWidget() )
        p->adjustSize();
}
//EVENTS
bool MyLineEdit::event(QEvent *event)
{
    return QLineEdit::event(event);
}
