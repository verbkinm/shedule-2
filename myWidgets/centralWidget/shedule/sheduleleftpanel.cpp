#include "sheduleleftpanel.h"

#include <QStyleOption>
#include <QPainter>
#include <QEvent>
#include <QMessageBox>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

static int resized = 0;

SheduleLeftPanel::SheduleLeftPanel(QWidget *parent) : QWidget(parent)
{
    pParent = parent;
    pLayout = new QVBoxLayout;

    pListLessons = new QTreeWidget;
    pListLessons->installEventFilter(this);
    pListLessons->setHeaderHidden(true);
    pListLessons->setAnimated(true);

    pItemRoot = new QTreeWidgetItem(pListLessons);
    pItemRoot->setText(0, "Предметы:");

    QFont *pFont = new QFont(pItemRoot->font(0));
    pFont->setPixelSize(24);
    pFont->setBold(true);
    pItemRoot->setFont(0,*pFont);
    pItemRoot->setIcon(0,QIcon(":/img/owl") );

//    pItemLesson = new QTreeWidgetItem;
    pItemLesson = 0;

//    pItemTeacher = new QTreeWidgetItem;
    pItemTeacher = 0;

    pLayout->addWidget(pListLessons);


    this->setContentsMargins(0,0,0,0);
    this->setLayout(pLayout);
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
//    while(!pFile->atEnd()) {
//        pItemLesson = new QTreeWidgetItem(pItemRoot);
//        pItemLesson->setText(0, pFile->read(1));
//        i++;
//    }
    pFile->close();
//    pListLessons->setItemExpanded();
}
void SheduleLeftPanel::traverseNode(const QDomNode& node)
{
   QDomNode domNode = node.firstChild();
   while(!domNode.isNull()) {
       if(domNode.isElement()) {
          QDomElement domElement = domNode.toElement();
          if(!domElement.isNull()) {
              if(domElement.tagName() == "lesson") {
                  pItemLesson = new QTreeWidgetItem(pItemRoot);
                  pItemLesson->setText(0, domElement.attribute("name", ""));
              }
              else {
                  pItemTeacher = new QTreeWidgetItem(pItemLesson);
                  pItemTeacher->setText(0, domElement.text() );
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
    qDebug() << "Event filters" << event->type();
    return QWidget::eventFilter(target, event);
}

bool SheduleLeftPanel::event(QEvent *event)
{
//    qDebug() << event->type();
    if(event->type() == QEvent::Resize && resized < 1){
        this->setUnits();
        resized = 1;
    }
    return QWidget::event(event);
}

