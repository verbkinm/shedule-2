#ifndef SHEDULERIGHT_H
#define SHEDULERIGHT_H

#include "shedulerighttablewidget.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class SheduleRight : public QWidget
{
    Q_OBJECT
public:
    SheduleRight(QWidget *parent = 0);

    void setHeaderText(QString str);
    void setUnits();

private:
    void paintEvent(QPaintEvent * );

    SheduleRightTableWidget* pSheduleRightTableWidget;
    QVBoxLayout* pLayout;
    QLabel* pHeader;

    bool event(QEvent *event);

signals:

public slots:
};

#endif // SHEDULERIGHT_H
