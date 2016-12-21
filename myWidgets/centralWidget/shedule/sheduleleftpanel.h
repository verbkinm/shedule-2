#ifndef SHEDULELEFTPANEL_H
#define SHEDULELEFTPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QFile>
#include <QDomDocument>
#include "inherited/mytreewidget.h"

class SheduleLeftPanel : public QWidget
{
    Q_OBJECT
public:
    SheduleLeftPanel(QWidget *parent);

    MyTreeWidget* pListLessons;
    QTreeWidgetItem *pItemLesson, *pItemTeacher, *pItemRoot; //список уроков и список учителей, pItemRoot - корень списка

private:
    QWidget* pParent;
    QVBoxLayout* pLayout;
    int startX, startY;

    void setUnits();

    void readFileLessons();
    void traverseNode(const QDomNode& node);

    bool event(QEvent *event);
    void paintEvent(QPaintEvent * );

    bool eventFilter(QObject *target, QEvent *event);

signals:
    void signalItemClick(QTreeWidgetItem*);
public slots:
    void slotItemClick(QTreeWidgetItem* item,int column);
    void slotItemExpanded(QTreeWidgetItem* item);
};

#endif // SHEDULELEFTPANEL_H
