#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H

#include <QTreeWidget>

class MyTreeWidget : public QTreeWidget
{
    Q_OBJECT
private:
    int startY, stopY;

    bool event(QEvent *event);
    QTreeWidgetItem* buffItem;
    void mouseReleaseEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);

public:
    MyTreeWidget();

    QTreeWidgetItem* rootItem;
    QScrollBar* sb;

signals:
    void signalItemClick(QTreeWidgetItem*);
private slots:
    void slotItemClick(QTreeWidgetItem* item, int column);
};

#endif // MYTREEWIDGET_H
