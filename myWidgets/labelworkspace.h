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
    LabelWorkSpace(QString text = 0, QString pixLabel = 0, QLabel *parent = 0);
    ~LabelWorkSpace();

    void applySize(QSize size);


signals:
  void signalClick();

private:
    QPixmap *pix_buff, *pix_push_buff, *buff, *label, *label_push;
    QPixmap *pix_resized, *pix_push_resized;
    QLabel* pL;
    QSize LabelSize, privSize;
    bool pressed;
    int currentWidth, currentHeight;

    QString textLabel;
    QLabel *pLText;
    QFont *font, *font_push;

    QRect rect;


    bool event(QEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

};

#endif // LABELWORKSPACE_H
