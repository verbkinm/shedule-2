#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H

#include <QTreeWidget>

class MyTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    MyTreeWidget();

    QTreeWidgetItem* rootItem;

private:
    int startX, startY, stopY;
    bool pressed;

//    bool event(QEvent *event);
    QTreeWidgetItem* buffItem;
    void mouseReleaseEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

signals:
    void signalItemClick(QTreeWidgetItem*);
private slots:
    void slotItemClick(QTreeWidgetItem* item, int column);

};

#endif // MYTREEWIDGET_H
