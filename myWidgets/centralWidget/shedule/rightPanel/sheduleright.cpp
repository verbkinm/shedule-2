#include "sheduleright.h"
#include "generalsettings.h"

#include <QStyleOption>
#include <QEvent>
#include <QPainter>
#include <QToolBox>
#include <QHeaderView>

#include <QDebug>

static int resized = 0;

//CONSTRUKTOR
SheduleRight::SheduleRight(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("SheduleRight");

    pLayout = new QVBoxLayout;
    pLayout->setMargin(0);
//    pLayout->setContentsMargins(0,0,0,0);
    pLayout->setSpacing(0);

    createHeader();
    creatTabs();

    pLayout->addWidget(pHeader);
    pLayout->addWidget(pTabWidget);

    this->setLayout(pLayout);
}
//FUNCTIONS
void SheduleRight::setHeaderText(QString str){
    pHeader->setText(str);
}
void SheduleRight::setUnits()
{
//    this->setFixedSize(this->size());
}
void SheduleRight::createHeader()
{
    pHeader = new QLabel(TEXT_SHEDULE_DEFAULT);
    QFont *pFont = new QFont(pHeader->font());
    pFont->setPixelSize(FONT_SHEDULE_RIGHT_HEADER);
    pFont->setBold(true);
    pHeader->setFont(*pFont);
    delete pFont;
    pHeader->setAlignment(Qt::AlignCenter);
    pHeader->setFixedHeight(HEADER_SIZE_HEIGHT);
}

void SheduleRight::creatTabs()
{
//    Shedule * parent = qobject_cast<Shedule*>(this->parent());

    pTabWidget = new QTabWidget(this);
    pSheduleTableWidget = new SheduleTableWidget;
    pTabWidget->addTab(pSheduleTableWidget, "Изменение в расписании");
    for (int i = 1; i < 12; ++i){
        QWidget *pNewTabWidget = new QWidget;
        pTabWidget->addTab(pNewTabWidget, QString::number(i)+"-е классы");
        QToolBox *pToolBox = new QToolBox(pNewTabWidget);
        for (int ii = 0; ii < 4; ++ii) {
            pToolBox->addItem(new QLabel(QString::number(ii)), QString::number(ii));
        }
        QVBoxLayout *pVBoxLayout = new QVBoxLayout;
        pVBoxLayout->addWidget(pToolBox);
        pNewTabWidget->setLayout(pVBoxLayout);
    }
}

//SLOTS
void SheduleRight::slotSetTableSize()
{
//    pSheduleRightTableWidget->setMaximumHeightTableWidget    (pTabWidget->widget(0)->size().height() \
//                                                              - pSheduleRightTableWidget->getHorizontalScroolBar()->height() \
//                                                              - pSheduleDateSwitch->height()); // ????
//    pSheduleRightTableWidget->setMaximumHeightTableWidgetLeft(pTabWidget->widget(0)->size().height() );
}
void SheduleRight::slotTest()
{

}

//EVENTS
bool SheduleRight::event(QEvent *event)
{
    if(this->isVisible() && event->type() == QEvent::Resize && resized < 1){
        setUnits();
        resized = 1;
    }
    return QWidget::event(event);
}
void SheduleRight::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
//DESTRUKTOR
SheduleRight::~SheduleRight()
{
    delete pHeader;
    delete pSheduleTableWidget;
    delete pTabWidget;
    delete pLayout;
}
