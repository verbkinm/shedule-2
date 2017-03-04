#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H

#include <QTreeWidget>
#include <QDomDocument>

class MyTreeWidget : public QTreeWidget
{
    Q_OBJECT
private:
    int startY, stopY;

    QTreeWidgetItem* buffItem;

    void mouseReleaseEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    bool event(QEvent *event);

public:
    MyTreeWidget();
    ~MyTreeWidget();

    QTreeWidgetItem *pItemLesson, *pItemTeacher, *pItemRoot;
    QScrollBar* sb;

    void traverseNode(const QDomNode& node);


signals:
    void signalItemClick(QTreeWidgetItem*);
    void signalItemRootClick();
private slots:
    void slotItemClick(QTreeWidgetItem* item, int column);
};

#endif // MYTREEWIDGET_H
