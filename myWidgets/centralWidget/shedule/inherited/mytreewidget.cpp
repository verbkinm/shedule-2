#include "mytreewidget.h"
#include "generalsettings.h"

#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QModelIndex>

MyTreeWidget::MyTreeWidget() : QTreeWidget(), pressed(false), stopY(-1), rootItem(0)
{
    this->setAnimated(true);
    this->setHeaderHidden(true);
    this->setExpandsOnDoubleClick(false);
    this->setRootIsDecorated(false);

    if(rootItem != 0)
        this->expandItem(rootItem);

    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*,int)), SLOT(slotItemClick(QTreeWidgetItem*,int)) );
}
void MyTreeWidget::slotItemClick(QTreeWidgetItem *item, int column)
{
    emit signalItemClick(item);

    if(!item->isExpanded())
        this->expandItem(item);
    else{
        if(item->text(column) == "Предметы:")
            this->collapseAll();
        this->collapseItem(item);
    }
}
void MyTreeWidget::mousePressEvent(QMouseEvent *event)
{
    buffItem = 0;
    qDebug() << "!!!!!!!!!";
    QTreeView::mousePressEvent(event);
    foreach (QTreeWidgetItem* item, this->selectedItems()) {
        if(item->isSelected()){
            buffItem = item;
            qDebug() << buffItem->text(0);
            item->setSelected(false);
            startY = QCursor::pos().y();
        }
    }
}
void MyTreeWidget::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << QCursor::pos();
    stopY=QCursor::pos().y();

    if (!event->buttons().testFlag(Qt::LeftButton))
        QTreeView::mouseMoveEvent(event);
}
void MyTreeWidget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "startY="<<startY;
    qDebug() << "stopY="<<stopY;

    if(stopY == -1){
        if(buffItem != 0){
            if(buffItem->text(0) == TEXT_ROOT_LIST){
                this->collapseAll();
                this->expandItem(rootItem);
            }
            else{
                this->setCurrentItem(buffItem);
                this->itemClicked(buffItem,0);
            }
        }
    }
    startY  = -1;
    stopY   = -1;
//    QTreeView::mouseReleaseEvent(event);
}

//bool MyTreeWidget::event(QEvent *event)
//{
////    if(event->type() == QEvent::Paint)
////        return QWidget::event(event);

//    qDebug() << this->objectName() << event->type();
//    return QWidget::event(event);
//}*/
