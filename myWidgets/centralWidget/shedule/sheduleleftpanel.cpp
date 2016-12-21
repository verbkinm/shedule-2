#include "sheduleleftpanel.h"
#include "generalsettings.h"

#include <QStyleOption>
#include <QPainter>
#include <QEvent>
#include <QMessageBox>
#include <QFileInfo>
#include <QDir>
#include <QScrollArea>
#include <QAbstractScrollArea>
#include <QScrollBar>
#include <QObject>
#include <QDebug>
#include <QMouseEvent>

static int resized = 0;

SheduleLeftPanel::SheduleLeftPanel(QWidget *parent) : QWidget(parent)
{
    pParent = parent;
    pLayout = new QVBoxLayout;

    pListLessons = new MyTreeWidget;
//    pListLessons->installEventFilter(this);
    pListLessons->setHeaderHidden(true);
    pListLessons->setAnimated(true);

    pItemRoot = new QTreeWidgetItem(pListLessons);
    pItemRoot->setText(0, TEXT_ROOT_LIST);

    QFont *pFont = new QFont(pItemRoot->font(0));
    pFont->setPixelSize(50);
    pFont->setBold(true);
    pItemRoot->setFont(0,*pFont);

//    pItemLesson = new QTreeWidgetItem;
    pItemLesson = 0;

//    pItemTeacher = new QTreeWidgetItem;
    pItemTeacher = 0;

    pLayout->addWidget(pListLessons);


    this->setContentsMargins(0,0,0,0);
    this->setLayout(pLayout);

//    connect(pListLessons, SIGNAL(itemClicked(QTreeWidgetItem*,int)), SLOT(slotItemClick(QTreeWidgetItem*,int))  );
//    connect(pItemRoot, SIGNAL,    SLOT(slotItemExpanded(QTreeWidgetItem*))   );
//    disconnect(pListLessons, SIGNAL(itemPressed(QTreeWidgetItem*,int)), SLOT(slotItemExpanded(QTreeWidgetItem*)) );
}
void SheduleLeftPanel::readFileLessons()
{
    QDomDocument domDoc;
    QFile* pFile = new QFile;
    pFile->setFileName(QString(QDir::currentPath() + "/" + "lessons.xml"));
    if (!pFile->open(QIODevice::ReadOnly) ) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        QFileInfo fileInfo(*pFile);
        msgBox.setText(QString("Невозможно открыть файл: " + fileInfo.filePath()) );// ->fileName());
        msgBox.exec();
        exit(1);
    }
    if(domDoc.setContent(pFile)) {
        QDomElement domElement= domDoc.documentElement();
        traverseNode(domElement);
    }
    pFile->close();
}
void SheduleLeftPanel::traverseNode(const QDomNode& node)
{

    QFont *pFont = new QFont(pItemRoot->font(0));
    pFont->setPixelSize(30);
    pFont->setBold(true);

   QDomNode domNode = node.firstChild();
   while(!domNode.isNull()) {
       if(domNode.isElement()) {
          QDomElement domElement = domNode.toElement();
          if(!domElement.isNull()) {
              if(domElement.tagName() == "lesson") {
                  pItemLesson = new QTreeWidgetItem(pItemRoot);
                  pItemLesson->setFont(0,*pFont);
                  pItemLesson->setText(0, domElement.attribute("name", ""));
              }
              else {
                  pItemTeacher = new QTreeWidgetItem(pItemLesson);
                  pItemTeacher->setFont(0,*pFont);
                  pItemTeacher->setText(0, domElement.text() );
                  pItemTeacher->setIcon(0,QPixmap(":/img/empty_button"));
                  qDebug() << "учитель\t" << domElement.text();
             }
          }
       }
       traverseNode(domNode);
       domNode = domNode.nextSibling();
    }
}
void SheduleLeftPanel::setUnits()
{
    this->setFixedSize(float(pParent->width()) / 100 * 25, pParent->height());
    readFileLessons();
    pListLessons->expandItem(pItemRoot);
}
void SheduleLeftPanel::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
bool SheduleLeftPanel::eventFilter(QObject *target, QEvent *event)
{
////    QWidget *widget = qobject_cast<QWidget *>(objectSender);
//    if (target == qobject_cast<QTreeWidget*>(target)) {
//        if (event->type() == QEvent::MouseButtonPress) {
//            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
//            if (mouseEvent->button() == Qt::RightButton){
//            qDebug() << "right mouse press";
//            return true;
//            }
//        } else {
//            return false;
//        }
//    } else {
//        // pass the event on to the parent class
//        return QWidget::eventFilter(target, event);
//    }
//    qDebug() << "target - " << target << endl << "Event filters" << event->type();
//    if(event->type() == QEvent::MouseButtonRelease ){
//        return QWidget::eventFilter(target, event);
//    }
}

bool SheduleLeftPanel::event(QEvent *event)
{
//    qDebug() << event->type();
    if(event->type() == QEvent::Resize && resized < 1){
        this->setUnits();
        resized = 1;
    }
//    if(event->type() == QEvent::LayoutRequest){
//        qDebug() << "click";
//        return false;
//    }
    return QWidget::event(event);
}
void SheduleLeftPanel::slotItemClick(QTreeWidgetItem *item, int column)
{
    emit signalItemClick(item);
    if(!item->isExpanded())
        pListLessons->expandItem(item);
    else{
        if(item->text(column) == "Предметы:")
            pListLessons->collapseAll();
        pListLessons->collapseItem(item);
    }
}
void SheduleLeftPanel::slotItemExpanded(QTreeWidgetItem *item)
{
    qDebug() << "expand - " << item->text(0);
}
