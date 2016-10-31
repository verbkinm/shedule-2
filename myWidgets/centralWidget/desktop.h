#ifndef DESKTOP_H
#define DESKTOP_H

#include <QWidget>
#include <QGridLayout>

#include "..\labelworkspace.h"

#define LABEL_COUNTS 6

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

    QGridLayout *pLayout;

    LabelWorkSpace *pLabelShedule[LABEL_COUNTS];

    void paintEvent(QPaintEvent * );
signals:

public slots:
};

#endif // DESKTOP_H
