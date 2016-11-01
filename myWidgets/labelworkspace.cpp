#include "labelworkspace.h"

#include <QStyleOption>
#include <QPainter>
#include <QDebug>


LabelWorkSpace::LabelWorkSpace(QSize centralWidget, QString pixLabel, QLabel *parent) : QLabel(parent), pressed(false)
{
    pix_buff = new QPixmap(":/img/glass");
    pix_push_buff = new QPixmap(":/img/glass_push");

    this->setAlignment(Qt::AlignCenter);
}
void LabelWorkSpace::applySize(QSize size)
{
    qDebug() << "!!!!!!!!!!!!!!!!!!! - " << size;

    float width;
//    switch (LABEL_COUNTS) {
//    case 1:
//        width = size.width() / LABEL_COUNTS * LABEL_COUNTS_ROWS - MARGIN_DESKTOP;
//        break;
//    case 2:

//        break;
//    case 3:

//        break;
//    case 4:

//        break;
//    case 5:

//        break;
//    case 6:

//        break;
//    case 7:

//        break;
//    case 8:

//        break;
//    case 9:
//        width = size.width() / LABEL_COUNTS * LABEL_COUNTS_ROWS - (size.width() / 100 * 20);
//        break;
//    default:
        width = size.width() / LABEL_COUNTS * LABEL_COUNTS_ROWS - MARGIN_DESKTOP;
//        break;
//    }
    float height;
    switch (LABEL_COUNTS_ROWS) {
    case 1:
        if(LABEL_COUNTS == 1)
            height = size.height() / LABEL_COUNTS * LABEL_COUNTS_ROWS - (size.height() / 100 * 25);
        else
            height = size.height() / LABEL_COUNTS * LABEL_COUNTS_ROWS + (size.height() / 100 * 10);
        break;
    case 2:
        height = size.height() / LABEL_COUNTS * LABEL_COUNTS_ROWS + (size.height() / 100 * 6) ;
        break;
    case 3:
        height = size.height() / LABEL_COUNTS * LABEL_COUNTS_ROWS - (size.height() / 100 * 12) ;
        break;
    default:
        height = size.height() / LABEL_COUNTS * LABEL_COUNTS_ROWS;
        break;
    }

    pix_resized = new QPixmap(pix_buff->scaled(width, height, Qt::KeepAspectRatio) );
    pix_push_resized = new QPixmap(pix_push_buff->scaled(width, height - (height / 100 * 2),Qt::KeepAspectRatio) );
    this->setPixmap(*pix_resized);
//    int height, width;
//    height = privSize.height() / 100 * 10;
//    width  = privSize.width()  / 100 * 10;
//    pix_resized = pix_buff->scaled(width, height, Qt::IgnoreAspectRatio);
//    pix_push_resized = pix_push_buff->scaled(width, height, Qt::IgnoreAspectRatio);

//    this->setPixmap(pix_resized);

//    delete pix_buff;

//    pL = new QLabel(this);
//    pL->setAlignment(Qt::AlignCenter);

//    currentWidth = this->width() / 100 * 40;
//    currentHeight = this->height() / 100 * 40;
//    label = new QPixmap(buff->scaled(currentWidth, currentHeight, Qt::KeepAspectRatio) );
//    label_push = new QPixmap(label->scaled(currentWidth-10, currentHeight-10, Qt::KeepAspectRatio) );
//    delete buff;
//    pL->setPixmap(*label);

//    pL->move(pix_resized.width() / 2 - label->width() / 2, pix_resized.height() / 2 - label->height() / 2 + float(30) / float(100) * 16);
}
void LabelWorkSpace::mouseMoveEvent(QMouseEvent *event)
{
  int x = event->pos().x();
  int y = event->pos().y();
  int sideX = this->width();
  int sideY = this->height();
  if(pressed){
    if(x < 0 || y < 0 || x > sideX || y > sideY){
      this->setPixmap(*pix_resized);
//      pL->setPixmap(*label);
      pressed = false;
    }
  }
  if(!pressed){
    if(x > 0 && x < sideX){
      if( y > 0 && y < sideY){
        this->setPixmap(*pix_push_resized);
//        pL->setPixmap(*label_push);
        pressed = true;
      }
    }
  }
}
bool LabelWorkSpace::event(QEvent *event)
{
  if(event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick ){
      pressed = true;
      this->setPixmap(*pix_push_resized);
//      pL->setPixmap(*label_push);
      return true;
  }
  if(event->type() == QEvent::MouseButtonRelease){
      if(!pressed){
          return true;
      }
      pressed = false;
      this->setPixmap(*pix_resized);
//      pL->setPixmap(*label);
      emit signalClick();
      return true;
  }
//    if(event->type() == QEvent::Resize)
//        this->setPixmap(*pix_buff);

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

