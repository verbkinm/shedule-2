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

    void setUnits();

private:
    int length;
    float currentSize;
    QString images[LABEL_COUNTS], labelText[LABEL_COUNTS];

    QGridLayout *pLayout;

    LabelWorkSpace *pLabelShedule[LABEL_COUNTS];

    bool event(QEvent *event);
    void paintEvent(QPaintEvent * );


signals:
    void signalLabel_0_Click();
    void signalLabel_1_Click();
    void signalLabel_2_Click();

public slots:
};

#endif // DESKTOP_H
