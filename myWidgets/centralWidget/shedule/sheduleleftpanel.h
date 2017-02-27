#ifndef SHEDULELEFTPANEL_H
#define SHEDULELEFTPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QFile>
#include <QDomDocument>
#include <QTabWidget>

#include "inherited/mytreewidget.h"
#include "inherited/verticallabel.h"

class SheduleLeftPanel : public QWidget
{
    Q_OBJECT
public:
    SheduleLeftPanel(QWidget *parent);

    MyTreeWidget* pListLessons;
    QTreeWidgetItem *pItemLesson, *pItemTeacher, *pItemRoot; //список уроков и список учителей, pItemRoot - корень списка
    VerticalLabel* pVerticalLabel;

private:
    QWidget* pParent;
    QVBoxLayout* pLayout;
    int startX, startY;

    void setUnits();

    void readFileLessons();
    void traverseNode(const QDomNode& node);

    bool event(QEvent *event);
    void paintEvent(QPaintEvent * );

signals:
    void signalItemClick(QTreeWidgetItem*);
public slots:
    void slotSwitchPanelToListLesson();
    void slotSwitchPanelToMini();
};

#endif // SHEDULELEFTPANEL_H
