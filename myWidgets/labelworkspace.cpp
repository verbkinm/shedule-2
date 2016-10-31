#include "labelworkspace.h"

#include <QStyleOption>
#include <QPainter>
#include <QDebug>

LabelWorkSpace::LabelWorkSpace(QSize centralWidget, QString pixLabel, QLabel *parent) : QLabel(parent), pressed(false)
{
    privSize = centralWidget;
    pix_buff = new QPixmap(":/img/glass");
    pix_push_buff = new QPixmap(":/img/glass_push");

    buff = new QPixmap(pixLabel);
}
void LabelWorkSpace::setSize()
{
    int height, width;
    height = privSize.height() / 100 * 55;
    width  = privSize.width()  / 100 * 60;
    pix_resized = pix_buff->scaled(width, height, Qt::IgnoreAspectRatio);
    pix_push_resized = pix_push_buff->scaled(width, height, Qt::IgnoreAspectRatio);

    this->setPixmap(pix_resized);

    delete pix_buff;

    pL = new QLabel(this);
    pL->setAlignment(Qt::AlignCenter);

    currentWidth = this->width() / 100 * 40;
    currentHeight = this->height() / 100 * 40;
    label = new QPixmap(buff->scaled(currentWidth, currentHeight, Qt::KeepAspectRatio) );
    label_push = new QPixmap(label->scaled(currentWidth-10, currentHeight-10, Qt::KeepAspectRatio) );
    delete buff;
    pL->setPixmap(*label);

    pL->move(pix_resized.width() / 2 - label->width() / 2, pix_resized.height() / 2 - label->height() / 2 + float(30) / float(100) * 16);
}
void LabelWorkSpace::mouseMoveEvent(QMouseEvent *event)
{
  int x = event->pos().x();
  int y = event->pos().y();
  int sideX = this->width();
  int sideY = this->height();
  if(pressed){
    if(x < 0 || y < 0 || x > sideX || y > sideY){
      this->setPixmap(pix_resized);
      pL->setPixmap(*label);
      pressed = false;
    }
  }
  if(!pressed){
    if(x > 0 && x < sideX){
      if( y > 0 && y < sideY){
        this->setPixmap(pix_push_resized);
        pL->setPixmap(*label_push);
        pressed = true;
      }
    }
  }
}
bool LabelWorkSpace::event(QEvent *event)
{
    qDebug() << "LabelWorkSpace " << this->size() << this->isVisible();
  if(event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick ){
      pressed = true;
      this->setPixmap(pix_push_resized);
      pL->setPixmap(*label_push);
      return true;
  }
  if(event->type() == QEvent::MouseButtonRelease){
      if(!pressed){
          return true;
      }
      pressed = false;
      this->setPixmap(pix_resized);
      pL->setPixmap(*label);
      emit signalClick();
      return true;
  }
  return QLabel::event(event);
}
//void LabelWorkSpace::paintEvent(QPaintEvent *)
//{
//    QStyleOption opt;
//    opt.init(this);
//    QPainter p(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
//}
LabelWorkSpace::~LabelWorkSpace()
{

}

