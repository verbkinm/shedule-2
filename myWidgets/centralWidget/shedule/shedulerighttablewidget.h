#ifndef SHEDULERIGHTTABLEWIDGET_H
#define SHEDULERIGHTTABLEWIDGET_H

#include "cell.h"

#include <QWidget>
#include <QDomDocument>

class SheduleRightTableWidget : public QWidget
{
    Q_OBJECT
private:
    QDomNode root;

    int numberOfLesson;
    int numberOfCollum;
    int numberOfClass;
    QString *pArrClassLiter; //number and literal
    QString *allFile;
    Cell **tableShedule;

    void structuring(QDomDocument *pDomDoc);
public:
    QDomDocument *pDomDoc;

    SheduleRightTableWidget(QWidget *parent = 0);

signals:

public slots:
};

#endif // SHEDULERIGHTTABLEWIDGET_H
