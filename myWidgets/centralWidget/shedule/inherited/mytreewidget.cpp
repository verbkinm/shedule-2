#include "mytreewidget.h"
#include "generalsettings.h"

//#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QModelIndex>
#include <QScrollBar>

MyTreeWidget::MyTreeWidget() : QTreeWidget(),startY(-1), stopY(-1), rootItem(0)
{
    this->setAnimated(true);
    this->setHeaderHidden(true);
    this->setExpandsOnDoubleClick(false);
    this->setRootIsDecorated(false);
    sb = this->verticalScrollBar();
    sb->setVisible(false);
    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*,int)), SLOT(slotItemClick(QTreeWidgetItem*,int)) );
}
void MyTreeWidget::slotItemClick(QTreeWidgetItem *item, int column)
{
    if(!item->isExpanded())
        this->expandItem(item);
    else{
        if(item->text(column) == TEXT_ROOT_LIST)
            this->collapseAll();
        this->collapseItem(item);
    }
}
void MyTreeWidget::mousePressEvent(QMouseEvent* event)
{
    buffItem = 0;
    QTreeView::mousePressEvent(event);
    foreach (QTreeWidgetItem* item, this->selectedItems()) {
        if(item->isSelected()){
            buffItem = item;
//            qDebug() << buffItem->text(0);
            item->setSelected(false);
            startY = QCursor::pos().y();
        }
    }
}
void MyTreeWidget::mouseMoveEvent(QMouseEvent* event)
{
//    qDebug() << QCursor::pos();
    stopY=QCursor::pos().y();

    sb->setVisible(true);
    if(startY < stopY){
        sb->setValue(sb->value() - 1);

    }
    if(startY > stopY)
        sb->setValue(sb->value() + 1);

    if (!event->buttons().testFlag(Qt::LeftButton))
        QTreeView::mouseMoveEvent(event);
}
void MyTreeWidget::mouseReleaseEvent(QMouseEvent*)
{
//    qDebug() << "startY="<<startY;
//    qDebug() << "stopY="<<stopY;

    if( ((startY - 20) < stopY && stopY < (startY + 20)) || stopY == -1){
        if(buffItem != 0){
            if(buffItem->text(0) == TEXT_ROOT_LIST){
                this->collapseAll();
                this->itemClicked(buffItem,0);
            }
            else{
                this->setCurrentItem(buffItem);
                this->itemClicked(buffItem,0);
            }
        }
    }
    startY  = -1;
    stopY   = -1;

    sb->setVisible(false);
//    QTreeView::mouseReleaseEvent(event); // нужно закоментировать, чтобы списки разворачивались
}

bool MyTreeWidget::event(QEvent *event)
{
    if(event->type() == QEvent::Show){
        this->collapseAll();
        this->itemClicked(rootItem,0);
    }
//    qDebug() << event->type();
    return QTreeView::event(event);
}
