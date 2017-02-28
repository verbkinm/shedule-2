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
#include <QDebug>
#include <QMouseEvent>

SheduleLeftPanel::SheduleLeftPanel(QWidget *parent) : QWidget(parent)
{
    pParent = parent;
    pLayout = new QVBoxLayout;
    pLayout->setMargin(0);

    pListLessons = new MyTreeWidget;
    pListLessons->hide();
    pListLessons->setFixedWidth(LEFT_PANEL_TREE_WIDTH);
    pItemRoot = new QTreeWidgetItem(pListLessons);
    pListLessons->rootItem = pItemRoot;
    pItemRoot->setText(0, TEXT_ROOT_LIST);

    QFont *pFont = new QFont(pItemRoot->font(0));
    pFont->setPixelSize(FONT_SHEDULE_LEFT_PANEL_TREE_ROOT);
    pFont->setBold(true);
    pItemRoot->setFont(0,*pFont);
    delete pFont;
    readFileLessons();
    this->pListLessons->expandItem(pItemRoot);

    pItemLesson = 0;
    pItemTeacher = 0;

    pVerticalLabel = new VerticalLabel(TEXT_VERTICAL_LABEL_LESSONS);

    pLayout->addWidget(pVerticalLabel);
    pLayout->addWidget(pListLessons);

    this->setContentsMargins(0,0,0,0);
    this->setLayout(pLayout);

    connect(pListLessons,   SIGNAL(itemClicked(QTreeWidgetItem*,int)), SIGNAL(signalItemClick(QTreeWidgetItem*))  );
    connect(pVerticalLabel, SIGNAL(signalClicked()), SLOT(slotSwitchPanelToListLesson()) );
    connect(pListLessons,   SIGNAL(signalItemRootClick()), SLOT(slotSwitchPanelToListLesson()) );// SLOT(slotSwitchPanelToMini()) );
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
             }
          }
       }
       traverseNode(domNode);
       domNode = domNode.nextSibling();
    }
   delete pFont;
}
void SheduleLeftPanel::setUnits()
{
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
//    if(event->type() == QEvent::Resize && resized < 1){
//        this->setUnits();
//        resized = 1;
//    }
    if(event->type() == QEvent::Show){
//        pListLessons->hide();
//        pVerticalLabel->setVisible(true);
        qDebug() << "show";
    }
    return QWidget::event(event);
}
void SheduleLeftPanel::slotSwitchPanelToListLesson()
{
    pListLessons->setVisible(!pListLessons->isVisible());
    pVerticalLabel->setVisible(!pVerticalLabel->isVisible());
    qDebug() << "pListLessons" << pListLessons->isVisible();
    qDebug() << "pVerticalLabel" << pVerticalLabel->isVisible();
//    this->setFixedWidth(this->width());
}
void SheduleLeftPanel::slotSwitchPanelToMini()
{
    pVerticalLabel->setVisible(true);
    pListLessons->setVisible(false);
//    this->adjustSize();
//    this->setFixedWidth(this->width());
}
