#ifndef TREEWIDGETITEM_H
#define TREEWIDGETITEM_H

#include <QTreeWidgetItem>


class TreeWidgetItem : public QTreeWidgetItem
{
public:
    TreeWidgetItem(QTreeWidget* parent = 0);
    TreeWidgetItem(QTreeWidgetItem *parent = 0);
};

#endif // TREEWIDGETITEM_H
