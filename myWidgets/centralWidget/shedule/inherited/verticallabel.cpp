#include "verticallabel.h"
#include "generalsettings.h"

#include <QPainter>
#include <QEvent>
#include <QMouseEvent>

#include <QDebug>

VerticalLabel::VerticalLabel(QString text)
{
    this->text = text;
    QFont font(this->font());
    font.setPixelSize(FONT_SHEDULE_LEFT_PANEL_TREE_TRAVERS_NODE);
    font.setBold(true);
    this->setFont(font);
    this->setMinimumWidth(VERTICAL_LABEL_WIDTH);
}
void VerticalLabel::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QTransform old = p.transform();
    p.translate(15,this->height()/2);
    p.rotate(-90);
    p.drawText(0,0, text);
    p.setTransform(old);
}
void VerticalLabel::mouseReleaseEvent(QMouseEvent*)
{
    emit signalClicked();
}
VerticalLabel::~VerticalLabel()
{
    qDebug() << "verticalLabel destruktor";
}
