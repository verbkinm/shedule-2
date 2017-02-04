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

    pItemRoot = new QTreeWidgetItem(pListLessons);
    pListLessons->rootItem = pItemRoot;
    pItemRoot->setText(0, TEXT_ROOT_LIST);

    QFont *pFont = new QFont(pItemRoot->font(0));
    pFont->setPixelSize(FONT_SHEDULE_LEFT_PANEL_TREE_ROOT);
    pFont->setBold(true);
    pItemRoot->setFont(0,*pFont);

    pItemLesson = 0;

    pItemTeacher = 0;

    pLayout->addWidget(pListLessons);


    this->setContentsMargins(0,0,0,0);
    this->setLayout(pLayout);

    connect(pListLessons, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this ,SIGNAL(signalItemClick(QTreeWidgetItem*))  );
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
    pFont->setPixelSize(FONT_SHEDULE_LEFT_PANEL_TREE_TRAVERS_NODE);
    pFont->setBold(true);

    pItemRoot->setTextAlignment(0,Qt::AlignHCenter);

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
//                  qDebug() << "учитель\t" << domElement.text();
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
bool SheduleLeftPanel::event(QEvent *event)
{
    if(event->type() == QEvent::Resize && resized < 1){
        this->setUnits();
        resized = 1;
    }
    return QWidget::event(event);
}
