#include "mytreewidget.h"
#include "generalsettings.h"

#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QModelIndex>
#include <QScrollBar>

static bool _expanded = false;

//CONSTRUKTOR
MyTreeWidget::MyTreeWidget() : QTreeWidget(),startY(-1), stopY(-1),pItemRoot(0)/*, rootItem(0)*/
{
    this->setAnimated(true);
    this->setHeaderHidden(true);
    this->setExpandsOnDoubleClick(false);
    this->setRootIsDecorated(false);

    sb = this->verticalScrollBar();
    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*,int)), SLOT(slotItemClick(QTreeWidgetItem*,int)) );

    sb->setFixedWidth(SCROLL_BAR_WIDTH - 5);
}
//FUNCTIONS
void MyTreeWidget::traverseNode(const QDomNode& node)
{
    QFont font = pItemRoot->font(0);
    font.setPixelSize(FONT_SHEDULE_LEFT_PANEL_TREE_TRAVERS_NODE);
    font.setBold(true);

    pItemRoot->setTextAlignment(0,Qt::AlignHCenter);

   QDomNode domNode = node.firstChild();
   while(!domNode.isNull()) {
       if(domNode.isElement()) {
          QDomElement domElement = domNode.toElement();
          if(!domElement.isNull()) {
              if(domElement.tagName() == "lesson") {
                  pItemLesson = new QTreeWidgetItem(pItemRoot);
                  pItemLesson->setFont(0,font);
                  pItemLesson->setText(0, domElement.attribute("name", ""));
              }
              else {
                  pItemTeacher = new QTreeWidgetItem(pItemLesson);
                  pItemTeacher->setFont(0,font);
                  pItemTeacher->setText(0, domElement.text() );
                  pItemTeacher->setIcon(0,QPixmap(":/img/empty_button"));
             }
          }
       }
       traverseNode(domNode);
       domNode = domNode.nextSibling();
    }
}
//SLOTS
void MyTreeWidget::slotItemClick(QTreeWidgetItem *item, int column)
{
    if(item->text(column) == TEXT_ROOT_LIST){
        emit signalItemRootClick();
        _expanded = false;
        return;
    }

    if(!item->isExpanded())
        this->expandItem(item);
    else{
//        if(item->text(column) == TEXT_ROOT_LIST)
//            emit signalItemRootClick();
        this->collapseItem(item);
    }
}
//EVENTS
void MyTreeWidget::mousePressEvent(QMouseEvent* event)
{
    buffItem = 0;
    QTreeView::mousePressEvent(event);
    foreach (QTreeWidgetItem* item, this->selectedItems()) {
        if(item->isSelected()){
            buffItem = item;
            item->setSelected(false);
            startY = QCursor::pos().y();
        }
    }
}
void MyTreeWidget::mouseMoveEvent(QMouseEvent* event)
{
        stopY=QCursor::pos().y();

//    sb->setVisible(true);
    if((startY + 10) < stopY){
        startY = stopY = QCursor::pos().y();
        sb->setValue(sb->value() - 1);
        buffItem = 0;
    }
    if((startY - 10) > stopY){
        startY = stopY = QCursor::pos().y();
        sb->setValue(sb->value() + 1);
        buffItem = 0;
    }

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
//                this->collapseAll();
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

//    sb->setVisible(false);
//    QTreeView::mouseReleaseEvent(event); // нужно закоментировать, чтобы списки разворачивались
}

bool MyTreeWidget::event(QEvent *event)
{
//    if(event->type() == QEvent::ContentsRectChange){
//        if(sb->isVisible() )
//        {
//            emit signalWidgetWidthChanged(LEFT_PANEL_TREE_WIDTH + sb->width());
//            this->setFixedWidth(this->width() + sb->width());
//        }
//        else{
//            this->setFixedWidth(LEFT_PANEL_TREE_WIDTH);
//        }
//    }
//    qDebug() << event->type();
    return QTreeView::event(event);
}
MyTreeWidget::~MyTreeWidget()
{
    this->clear();
    qDebug() << "mytreewidget destruktor";
}
