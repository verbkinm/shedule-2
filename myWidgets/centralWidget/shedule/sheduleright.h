#ifndef SHEDULERIGHT_H
#define SHEDULERIGHT_H

#include <QWidget>

class SheduleRight : public QWidget
{
    Q_OBJECT
public:
    SheduleRight(QWidget *parent = 0);

private:
    void paintEvent(QPaintEvent * );

signals:

public slots:
};

#endif // SHEDULERIGHT_H
