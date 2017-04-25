#ifndef SHEDULERIGHT_H
#define SHEDULERIGHT_H

#include "firstTab/sheduletablewidget.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>

class SheduleRight : public QWidget
{
    Q_OBJECT
public:
    SheduleRight(QWidget *parent = 0);
    ~SheduleRight();

    void setHeaderText(QString str, QString lesson, QString teacher);
    void setUnits();

private:
    void paintEvent(QPaintEvent * );

    QVBoxLayout                 *pLayout;
    QLabel                      *pHeader;
    QTabWidget                  *pTabWidget;

    SheduleTableWidget          *pSheduleTableWidget;

    void createHeader();
    void creatTabs();
    bool event(QEvent *event);

signals:

public slots:
    void slotTest();
    void slotSetTableSize();
};

#endif // SHEDULERIGHT_H
