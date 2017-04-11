#include "sheduleleftpanel.h"
#include "generalsettings.h"

#include <QStyleOption>
#include <QPainter>
#include <QEvent>
#include <QMessageBox>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QMouseEvent>

#define OBJECT_NAME_VERTICAL_LABEL "pVerticalLabel"
#define OBJECT_NAME_LIST_LESSON "pListLessons"

//CONSTRUKTOR
SheduleLeftPanel::SheduleLeftPanel(QWidget *parent) : QWidget(parent)
{
    pLayout = new QVBoxLayout;
    pLayout->setMargin(0);

    //VERTICAL_LABEL
    pVerticalLabel = new VerticalLabel(TEXT_VERTICAL_LABEL_LESSONS);
    pVerticalLabel->setObjectName(OBJECT_NAME_VERTICAL_LABEL);
    pLayout->addWidget(pVerticalLabel);
    connect(pVerticalLabel, SIGNAL(signalClicked()),  this, SLOT(slotSwitchPanelToListLesson()) );
    //LIST_LESSON
    pListLessons = new MyTreeWidget;
    pListLessons->setObjectName(OBJECT_NAME_LIST_LESSON);
    pListLessons->setFixedWidth(LEFT_PANEL_TREE_WIDTH);
    pListLessons->pItemRoot = new QTreeWidgetItem(pListLessons);
    pListLessons->pItemRoot->setText(0, TEXT_ROOT_LIST);
    readFileLessons();
    QFont font = pListLessons->pItemRoot->font(0);
    font.setPixelSize(FONT_SHEDULE_LEFT_PANEL_TREE_ROOT);
    font.setBold(true);
    pListLessons->pItemRoot->setFont(0,font);
    pListLessons->expandItem(pListLessons->pItemRoot);
    pListLessons->pItemLesson = 0;
    pListLessons->pItemTeacher = 0;
    pLayout->addWidget(pListLessons);
    pListLessons->hide();

    connect(pListLessons,   SIGNAL(signalItemRootClick()),  SLOT(slotSwitchPanelToListLesson()) );
    connect(pListLessons,   SIGNAL(itemClicked(QTreeWidgetItem*, int)),  this, SIGNAL(signalItemClick(QTreeWidgetItem*, int)) );
    connect(pListLessons, SIGNAL(signalWidgetWidthChanged(int)), this, SLOT(slotResizeWidth(int)) );


    this->setContentsMargins(0,0,0,0);
    this->setLayout(pLayout);
}
//FUNCTIONS
void SheduleLeftPanel::createVerticalLabel()
{
    pVerticalLabel = new VerticalLabel(TEXT_VERTICAL_LABEL_LESSONS);
    pVerticalLabel->setObjectName(OBJECT_NAME_VERTICAL_LABEL);
    pLayout->addWidget(pVerticalLabel);
    connect(pVerticalLabel, SIGNAL(signalClicked()),  this, SLOT(slotSwitchPanelToListLesson()) );
}
void SheduleLeftPanel::deleteVerticalLabel()
{
//    disconnect(pVerticalLabel, SIGNAL(signalClicked()), this, SLOT(slotSwitchPanelToListLesson()) );
    delete pVerticalLabel;
}
void SheduleLeftPanel::createListLesson()
{
    pListLessons = new MyTreeWidget;
    pListLessons->setObjectName(OBJECT_NAME_LIST_LESSON);
    pListLessons->setFixedWidth(LEFT_PANEL_TREE_WIDTH);
    pListLessons->pItemRoot = new QTreeWidgetItem(pListLessons);
    pListLessons->pItemRoot->setText(0, TEXT_ROOT_LIST);
    readFileLessons();
    QFont font = pListLessons->pItemRoot->font(0);
    font.setPixelSize(FONT_SHEDULE_LEFT_PANEL_TREE_ROOT);
    font.setBold(true);
    pListLessons->pItemRoot->setFont(0,font);
    pListLessons->expandItem(pListLessons->pItemRoot);
    pListLessons->pItemLesson = 0;
    pListLessons->pItemTeacher = 0;
    pLayout->addWidget(pListLessons);
    this->setMaximumWidth(pListLessons->width());

    connect(pListLessons,   SIGNAL(signalItemRootClick()),  SLOT(slotSwitchPanelToListLesson()) );
    connect(pListLessons,   SIGNAL(itemClicked(QTreeWidgetItem*, int)),  this, SIGNAL(signalItemClick(QTreeWidgetItem*, int)) );
}
void SheduleLeftPanel::deleteListLesson()
{
//    disconnect(pListLessons, SIGNAL(signalItemRootClick()), this, SLOT(slotSwitchPanelToListLesson()) );
    delete pListLessons;
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
        pListLessons->traverseNode(domElement);
    }
    pFile->close();
}
void SheduleLeftPanel::setUnits()
{
//    readFileLessons();
//    pListLessons->expandItem(pItemRoot);
}
//SLOTS
void SheduleLeftPanel::slotResizeWidth(int w)
{
    this->setFixedWidth(w);
}

void SheduleLeftPanel::slotSwitchPanelToListLesson()
{
    QObject *object = this->sender();
    if(object->objectName() == OBJECT_NAME_LIST_LESSON){
        pListLessons->hide();
        pVerticalLabel->setVisible(true);
//        deleteListLesson();
//        createVerticalLabel();
        return;
    }
    if(object->objectName() == OBJECT_NAME_VERTICAL_LABEL){
        pVerticalLabel->hide();
        pListLessons->setVisible(true);
        pListLessons->collapseAll();
        pListLessons->expandItem(pListLessons->pItemRoot);
        this->setMaximumWidth(pListLessons->width());
//        deleteVerticalLabel();
//        createListLesson();
    }
}
//EVENTS
void SheduleLeftPanel::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
bool SheduleLeftPanel::event(QEvent *event)
{
//    qDebug() << event->type();
//    if(event->type() == QEvent::Resize && resized < 1){
//        this->setUnits();
//        resized = 1;
//    }
    return QWidget::event(event);
}
//DECONSTRUKTOR
SheduleLeftPanel::~SheduleLeftPanel()
{
    qDebug() << "sheduleLeftPanel destruktor";
}
