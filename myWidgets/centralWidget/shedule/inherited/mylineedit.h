#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    MyLineEdit( QWidget* p = 0 );

    QSize sizeHint();
    QSize minimumSizeHint();

private:
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void mouseDoubleClickEvent(QMouseEvent*);

    bool event(QEvent *event);

private slots:
    void slotResizeByContents();
};

#endif // MYLINEEDIT_H
