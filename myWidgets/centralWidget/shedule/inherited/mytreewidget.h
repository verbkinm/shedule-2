#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H

#include <QTreeWidget>

class MyTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    MyTreeWidget();

    QTreeWidgetItem* rootItem;
    QScrollBar* sb;

private:
    int startY, stopY;

    bool event(QEvent *event);
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
