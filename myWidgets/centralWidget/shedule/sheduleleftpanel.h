#ifndef SHEDULELEFTPANEL_H
#define SHEDULELEFTPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QFile>
#include <QDomDocument>
//#include "TreeWidgetItem/treewidgetitem.h"

class SheduleLeftPanel : public QWidget
{
    Q_OBJECT
public:
    SheduleLeftPanel(QWidget *parent = 0);

    QTreeWidget* pListLessons;
    QTreeWidgetItem *pItemLesson, *pItemTeacher, *pItemRoot; //список уроков и список учителей

    void setUnits();

private:
    QWidget* pParent;
    QVBoxLayout* pLayout;

    void readFileLessons();
    void traverseNode(const QDomNode& node);

    bool event(QEvent *event);
    void paintEvent(QPaintEvent * );

    bool eventFilter(QObject *target, QEvent *event);

signals:

public slots:
};

#endif // SHEDULELEFTPANEL_H
