#include "mytreewidget.h"
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>

MyTreeWidget::MyTreeWidget() : QTreeWidget(), pressed(false)
{

    connect(this, SIGNAL(viewportEntered()), SLOT(slotView()) );
}
void MyTreeWidget::slotView()
{
    qDebug() << "slot";
}

void MyTreeWidget::mouseMoveEvent(QMouseEvent *event)
{

    qDebug() << QCursor::pos();
}
void MyTreeWidget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "&&&&&&&&&&&&&&&&&&&&&&&&&";
    foreach (QTreeWidgetItem* item, this->selectedItems()) {
        if(item->isSelected()){
            if(!item->isExpanded())
                this->expandItem(item);
            else{
                if(item->text(0) == "Предметы:")
                    this->collapseAll();
                this->collapseItem(item);
            }
        }
    }
}

bool MyTreeWidget::event(QEvent *event)
{
//    if(event->type() == QEvent::Paint)
//        return QWidget::event(event);

    qDebug() << this->objectName() << event->type();
    return QWidget::event(event);
}
