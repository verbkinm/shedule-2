#include "labelworkspace.h"

#include <QStyleOption>
#include <QPainter>
//#include <QDebug>
#include <QVBoxLayout>
#include <QRect>

LabelWorkSpace::LabelWorkSpace(QString text, QString pixLabel, QLabel *parent) : QLabel(parent), pressed(false)
{
    pix_buff = new QPixmap(":/img/glass");
    pix_push_buff = new QPixmap(":/img/glass_push");

    buff = new QPixmap(pixLabel);

    textLabel = text;

    this->setAlignment(Qt::AlignCenter);
}
void LabelWorkSpace::applySize(QSize size)
{
    float width = size.width() / LABEL_COUNTS * LABEL_COUNTS_ROWS - MARGIN_DESKTOP;
    float height;
    switch (LABEL_COUNTS_ROWS) {
    case 1:
        if(LABEL_COUNTS == 1)
            height = size.height() / LABEL_COUNTS * LABEL_COUNTS_ROWS - (size.height() / 100 * 25);
        else
            height = size.height() / LABEL_COUNTS * LABEL_COUNTS_ROWS + (size.height() / 100 * 10);
        break;
    case 2:
        height = size.height() / LABEL_COUNTS * LABEL_COUNTS_ROWS + (size.height() / 100 * 15) ;
        break;
    case 3:
        height = size.height() / LABEL_COUNTS * LABEL_COUNTS_ROWS - (size.height() / 100 * 50) ;
        break;
    default:
        height = size.height() / LABEL_COUNTS * LABEL_COUNTS_ROWS;
        break;
    }

    pix_resized = new QPixmap(pix_buff->scaled(width, height, Qt::KeepAspectRatio,Qt::SmoothTransformation) );
    pix_push_resized = new QPixmap(pix_push_buff->scaled(width, height - (height / 100 * 2),Qt::KeepAspectRatio,Qt::SmoothTransformation) );
    this->setPixmap(*pix_resized);
    pL = new QLabel;
    label = new QPixmap(buff->scaled(pix_resized->width(), pix_resized->height() - height / 100 * 50, Qt::KeepAspectRatio,Qt::SmoothTransformation) );
    label_push = new QPixmap(buff->scaled(pix_push_resized->width(), pix_push_resized->height() - height / 100 * 50, Qt::KeepAspectRatio,Qt::SmoothTransformation) );
    delete buff;
    pL->setPixmap(*label);

    pL->setAlignment(Qt::AlignCenter);

    QVBoxLayout* l = new QVBoxLayout;
    l->setAlignment(Qt::AlignCenter);
    l->setMargin(0);

    l->addWidget(pL);

    pLText = new QLabel(textLabel);

    font = new QFont(pLText->font());
    font->setPixelSize(FONT_SIZE_LABEL_WORK_SPACE);
    font_push = new QFont(pLText->font());
    font_push->setPixelSize(FONT_PUSH_SIZE);

    pLText->setFont(*font);
    pLText->setAlignment(Qt::AlignCenter);

    l->addWidget(pLText);

    this->setLayout(l);
//    int x = ((this->width() - pix_resized->width()) / 2) + ((this->height() - pix_resized->height())/2);
    int x1 = this->geometry().x();
    int y1 = this->geometry().y();
    int x2 = this->geometry().x()+this->width();
    int y2 = this->geometry().y()+this->height();
    rect.setCoords(x1,y1,x2,y2);
}
void LabelWorkSpace::mouseMoveEvent(QMouseEvent *event)
{
  int x = event->pos().x() - 50;
  int y = event->pos().y();
  int sideX = this->width() - 100;
  int sideY = this->height();
  if(pressed){
    if(x < 0 || y < 0 || x > sideX || y > sideY){
      this->setPixmap(*pix_resized);
      pL->setPixmap(*label);
      pLText->setFont(*font);
      pressed = false;
    }
  }
  if(!pressed){
    if(x > 0 && x < sideX){
      if( y > 0 && y < sideY){
        this->setPixmap(*pix_push_resized);
        pL->setPixmap(*label_push);
        pLText->setFont(*font_push);
        pressed = true;
      }
    }
  }
}
bool LabelWorkSpace::event(QEvent *event)
{
  if(this->isEnabled()){
      if(event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick ){
          pressed = true;
          this->setPixmap(*pix_push_resized);
          pL->setPixmap(*label_push);
          pLText->setFont(*font_push);
          return true;
      }
      if(event->type() == QEvent::MouseButtonRelease){
          if(!pressed){
              return true;
          }
          pressed = false;
          this->setPixmap(*pix_resized);
          pL->setPixmap(*label);
          pLText->setFont(*font);
          emit signalClick();
          return true;
      }
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
    delete pix_buff;
    delete pix_push_buff;
    delete pix_resized;
    delete pix_push_resized;
    delete pL;
    delete label;
    delete label_push;
    delete font;
    delete font_push;
}

