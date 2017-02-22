#ifndef SHEDULERIGHTTABLEWIDGET_H
#define SHEDULERIGHTTABLEWIDGET_H

#include "cell.h"

#include <QWidget>
#include <QDomDocument>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QVBoxLayout>

class SheduleRightTableWidget : public QWidget
{
    Q_OBJECT
private:
    QDomNode root;

    int numberOfLesson;
    int numberOfCollum;
    int numberOfClass;
    QString *pArrClassLiter; //number and literal
    QString *pArrLessonTime;
    QString *allFile;
    Cell **tableShedule;

    QTableWidget *pTableWidget;
    QTableWidgetItem *pTableWidgetItem;

    QVBoxLayout *pLayout;

    void structuring(QDomDocument *pDomDoc);

    void paintEvent(QPaintEvent * );
public:
    QDomDocument *pDomDoc;

    SheduleRightTableWidget(QWidget *parent = 0);

signals:

public slots:
};

#endif // SHEDULERIGHTTABLEWIDGET_H
