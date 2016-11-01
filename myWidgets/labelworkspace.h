#ifndef LABELWORKSPACE_H
#define LABELWORKSPACE_H

#include <QLabel>
#include <QObject>
#include <QEvent>
#include <QMouseEvent>

#include "../generalsettings.h"

class LabelWorkSpace : public QLabel
{
    Q_OBJECT
public:
    LabelWorkSpace(QSize centralWidget, QString pixLabel = 0, QLabel *parent = 0);
    ~LabelWorkSpace();

    void applySize(QSize size);
//    virtual void paintEvent(QPaintEvent * );

signals:
  void signalClick();

private:
    QPixmap *pix_buff, *pix_push_buff, *buff, *label, *label_push;
    QPixmap *pix_resized, *pix_push_resized;
    QLabel* pL;
    QSize LabelSize, privSize;
    bool pressed;
    int currentWidth, currentHeight;

    bool event(QEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
//    void paintEvent(QPaintEvent *);
};

#endif // LABELWORKSPACE_H
