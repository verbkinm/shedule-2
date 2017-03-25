#include "sheduledateswitch.h"
#include "generalsettings.h"

#include <QDate>
#include <QDir>
#include <QColor>
#include <QPalette>
#include <QStyleOption>
#include <QPainter>
#include <QFileInfo>

#include <QDebug>

//CONSTRUKTOR
SheduleDateSwitch::SheduleDateSwitch(QWidget *parent) : QWidget(parent)
{
    QSize size(SHEDULE_DATE_SWITCH_BUTTON_SIZE,SHEDULE_DATE_SWITCH_BUTTON_SIZE);
    pPreviousDay= new PushButton(":/img/previos_button", ":/img/previos_button_push", size);
    pPreviousDay->setEnabled(false);
    pNextDay    = new PushButton(":/img/next_button", ":/img/next_button_push", size);
    pNextDay->setEnabled(false);

    pDate       = new MyLineEdit;
    pDate->setAlignment(Qt::AlignCenter);
    pDate->setReadOnly(true);

    pLayout     = new QHBoxLayout;
    pLayout->addWidget(pPreviousDay);
    pLayout->addWidget(pDate);
    pLayout->addWidget(pNextDay);

    this->setLayout(pLayout);

    connect(pPreviousDay, SIGNAL(signalClick()), SIGNAL(signalPreviosDay())  );
    connect(pNextDay    , SIGNAL(signalClick()), SIGNAL(signalNextDay())     );
//    this->setFixedWidth(SHEDULE_DATE_SIZE_WIDTH);
}
//FUNCTIONS
void SheduleDateSwitch::setButtonsState()
{
    QString currentDay, currentMonth, currentYear, currentFile;
    QStringList list = pDate->text().split(" - ");

    currentDay      = list.at(0);
    currentMonth    = list.at(1);
    currentYear     = list.at(2);
    currentFile     = currentDay.append(".xml");

    QDir dirYear(LOCAL_ARCHIVE_PATH + PATH_SPLITER + currentYear );
    if(dirYear.exists()){
        QDir dirMonth(dirYear.absolutePath() + PATH_SPLITER + currentMonth);
        if(dirMonth.exists()){
            foreach (QString str, dirMonth.entryList(QDir::Files | QDir::NoDotAndDotDot)) {
                qDebug() << str;
            }
        }
    }
    qDebug() << currentDay << currentMonth << currentYear;
}
void SheduleDateSwitch::setSheduleDateSwitch(QString date)
{
    int i = -1;
    if(date.endsWith("сегодня.xml"))
        date = QDate::currentDate().toString("dd - MM - yyyy");
    else if(date.endsWith("завтра.xml")){
        int day = QDate::currentDate().day() + 1;
        date = QString::number(day) + QDate::currentDate().toString(" - MM - yyyy");
    }
    else if( (i = date.indexOf("архив")) != -1){
        QStringList tmp= date.mid(i).remove("архив/").remove(".xml").split("/");
        date = tmp.at(2) + " - " + tmp.at(1) + " - " + tmp.at(0);
    }

    this->pDate->setText(date);
    setButtonsState();
}
//SLOTS
void SheduleDateSwitch::slotSetDateSheduleDateSwitch()
{
    qDebug() << "signal - slot ";//<< QFileInfo(*file).absoluteFilePath();
}
//EVENTS
void SheduleDateSwitch::paintEvent(QPaintEvent * )
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
//DESTRUKTOR
SheduleDateSwitch::~SheduleDateSwitch()
{
    delete pNextDay;
    delete pPreviousDay;
    delete pLayout;
    delete pDate;
}
