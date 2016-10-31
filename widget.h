#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>

#include "header.h"
#include "center.h"
#include "footer.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

  Header *header;
  Center *center;
  Footer *footer;


  QVBoxLayout *pMainLayout;
};

#endif // WIDGET_H
