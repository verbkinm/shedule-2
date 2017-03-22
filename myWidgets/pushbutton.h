#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QLabel>
#include <QEvent>
#include <QSize>
#include <QMouseEvent>

class PushButton : public QLabel
{
  Q_OBJECT
public:
  PushButton(QString icon, QString icon_push, unsigned int w = 0, unsigned int h = 0);
  PushButton(QString icon, QString icon_push, QSize size);

  void setSize(QSize size);
  void setSize(int w, int h);

signals:
  void signalClick();


private:
  QPixmap *pix_buff, *pix_push_buff;
  QPixmap pix_resized, pix_push_resized;
  QSize buttonSize;
  bool pressed;

  bool event(QEvent *event);
  virtual void mouseMoveEvent(QMouseEvent *event);

};

#endif // PUSHBUTTON_H
