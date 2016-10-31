#ifndef CENTER_H
#define CENTER_H

#include <QWidget>
#include <QVBoxLayout>
#include "myWidgets/centralWidget/desktop.h"

class Center : public QWidget
{
    Q_OBJECT
public:
    Center(QWidget *parent = 0);
    ~Center();

    void applySize(void);

private:
    int length;
    float currentSize;

    QVBoxLayout *pLayout;

    void paintEvent(QPaintEvent * );

    Desktop *desktop;

signals:

public slots:
};

#endif // CENTER_H
