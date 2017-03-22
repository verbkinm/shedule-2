#include "pushbutton.h"
//#include <QDebug>

PushButton::PushButton(QString icon, QString icon_push, unsigned int w, unsigned int h) : QLabel(), pressed(false)
{
  pix_buff = new QPixmap(icon);
  pix_push_buff = new QPixmap(icon_push);

  if(w > 0 && h > 0)
    this->setSize(w, h);
}
PushButton::PushButton(QString icon, QString icon_push, QSize size)
{
    pix_buff        = new QPixmap(icon);
    pix_push_buff   = new QPixmap(icon_push);

    if(size.width() > 0 && size.height() > 0)
      this->setSize(size.width(), size.height());
}

void PushButton::setSize(QSize size)
{
  buttonSize = size;
  this->setFixedSize(buttonSize);

  pix_resized = pix_buff->scaled(size, Qt::KeepAspectRatio,Qt::SmoothTransformation);
  pix_push_resized = pix_push_buff->scaled(size, Qt::KeepAspectRatio,Qt::SmoothTransformation);

  this->setPixmap(pix_resized);

  delete pix_buff;
  delete pix_push_buff;
}
void PushButton::setSize(int w, int h)
{
    this->setSize(QSize(w, h));
}

void PushButton::mouseMoveEvent(QMouseEvent *event)
{
  int x = event->pos().x();
  int y = event->pos().y();
  int side = this->width();
  if(pressed){
    if(x < 0 || y < 0 || x > side || y > side){
      this->setPixmap(pix_resized);
      pressed = false;
    }
  }
  if(!pressed){
    if(x > 0 && x < side){
      if( y > 0 && y < side){
        this->setPixmap(pix_push_resized);
        pressed = true;
      }
    }
  }
}
bool PushButton::event(QEvent *event)
{
  if( (this->isEnabled()) && (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick) ){
      pressed = true;
      this->setPixmap(pix_push_resized);
      return true;
  }
  if(event->type() == QEvent::MouseButtonRelease){
      if(!pressed){
          return true;
      }
      pressed = false;
      this->setPixmap(pix_resized);
      emit signalClick();
      return true;
  }
  return QLabel::event(event);
}

