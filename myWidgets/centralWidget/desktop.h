#ifndef DESKTOP_H
#define DESKTOP_H

#include <QWidget>
#include <QGridLayout>

#include "../labelworkspace.h"



class Desktop : public QWidget
{
    Q_OBJECT
public:
    Desktop(QWidget *parent = 0);
    ~Desktop();


//    void setSize();
private:
    int length;
    float currentSize;
    QString images[LABEL_COUNTS];

    QGridLayout *pLayout;

    LabelWorkSpace *pLabelShedule[LABEL_COUNTS];

    void setUnits();

    bool event(QEvent *event);
    void paintEvent(QPaintEvent * );

signals:

public slots:
};

#endif // DESKTOP_H
