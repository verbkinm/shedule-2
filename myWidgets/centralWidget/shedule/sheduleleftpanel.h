#ifndef SHEDULELEFTPANEL_H
#define SHEDULELEFTPANEL_H

#include <QVBoxLayout>
#include <QTreeWidgetItem>
#include <QFile>
//#include <QDomDocument>
#include <QTabWidget>

#include "inherited/mytreewidget.h"
#include "inherited/verticallabel.h"

class SheduleLeftPanel : public QWidget
{
    Q_OBJECT
public:
    SheduleLeftPanel(QWidget *parent = 0);
    ~SheduleLeftPanel();

    MyTreeWidget* pListLessons;
//    QTreeWidgetItem *pItemLesson, *pItemTeacher, *pItemRoot; //список уроков и список учителей, pItemRoot - корень списка
    VerticalLabel* pVerticalLabel;

private:
    QVBoxLayout* pLayout;

    void setUnits();
    void createListLesson();
    void deleteListLesson();

    void createVerticalLabel();
    void deleteVerticalLabel();

    void readFileLessons();
//    void traverseNode(const QDomNode& node);

    bool event(QEvent *event);
    void paintEvent(QPaintEvent * );

signals:
    void signalItemClick(QTreeWidgetItem*);
    void signalTest();
public slots:
    void slotSwitchPanelToListLesson();
//    void slotSwitchPanelToMini();
};

#endif // SHEDULELEFTPANEL_H
