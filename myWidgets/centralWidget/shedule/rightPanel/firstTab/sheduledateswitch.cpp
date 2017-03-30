#include "sheduledateswitch.h"
#include "generalsettings.h"

#include <QDate>
#include <QDir>
#include <QColor>
#include <QPalette>
#include <QStyleOption>
#include <QPainter>
#include <QFileInfo>
#include <QFile>

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

    QFont font;
    font = pDate->font();
    font.setBold(true);
    font.setPixelSize(SHEDULE_DATE_TEXT_SIZE);
    pDate->setFont(font);

    connect(pPreviousDay, SIGNAL(signalClick()), SLOT(slotPreviosDay())  );
    connect(pNextDay    , SIGNAL(signalClick()), SLOT(slotNextDay())     );
//    this->setFixedWidth(SHEDULE_DATE_SIZE_WIDTH);
}
//FUNCTIONS
void SheduleDateSwitch::setButtonsState()
{
    QString currentDay, currentMonth, currentYear;
    QStringList list = pDate->text().split(" - ");

    currentDay      = list.at(0);
    currentMonth    = list.at(1);
    currentYear     = list.at(2);

    if(!checkDatePrevios(currentYear, currentMonth, currentDay) )
        pPreviousDay->setEnabled(false);

    if(!checkDateNext(currentYear, currentMonth, currentDay) )
        pNextDay->setEnabled(false);


    qDebug() << "previosFileName" << previosFileName;
    qDebug() << "nextFileName" << nextFileName;
}
bool SheduleDateSwitch::checkDatePrevios(QString year, QString month, QString day)
{
    if(year == SHEDULE_DATE_ARCHIVE_LIMIT_MIN)
        return false;

    QDir dirYear(LOCAL_ARCHIVE_PATH + PATH_SPLITER + year);
    if(dirYear.exists()){
        QDir dirMonth(dirYear.absolutePath() + PATH_SPLITER + month);
        if(dirMonth.exists()){
            if(day.toInt() < 33 && day.toInt() > 0){
                    day = QString::number(day.toInt() - 1);

                if(day.toInt() < 10 && day.toInt() > 0)
                    day.prepend("0");

                QFile file(QString(dirMonth.absolutePath() + QString(PATH_SPLITER) + day + ".xml"));
                if(file.exists()){
                    pPreviousDay->setEnabled(true);
                    previosFileName = QFileInfo(file).absoluteFilePath();
                    return true;
                }
                if(checkDatePrevios(year, month, day) )
                    return true;
            }

        }
        day = "32";

        if(month.toInt() < 13 && month.toInt() > 0){
            month = QString::number(month.toInt() - 1);

            if(month.toInt() < 10 && month.toInt() > 0)
                month.prepend("0");
            if(checkDatePrevios(year, month, day) )
                return true;
        }
    }
    year = QString::number(year.toInt() - 1);

    month = "12";

    if(checkDatePrevios(year, month, day) )
        return true;

    return false;
}
bool SheduleDateSwitch::checkDateNext(QString year, QString month, QString day)
{
    if(year == SHEDULE_DATE_ARCHIVE_LIMIT_MAX)
        return false;

    QDir dirYear(LOCAL_ARCHIVE_PATH + PATH_SPLITER + year);
    if(dirYear.exists()){
        QDir dirMonth(dirYear.absolutePath() + PATH_SPLITER + month);
        if(dirMonth.exists()){
            if(day.toInt() < 31 && day.toInt() > -1){
                    day = QString::number(day.toInt() + 1);

                if(day.toInt() < 10 && day.toInt() > 0)
                    day.prepend("0");

                QFile file(QString(dirMonth.absolutePath() + QString(PATH_SPLITER) + day + ".xml"));
                if(file.exists()){
                    pNextDay->setEnabled(true);
                    nextFileName = QFileInfo(file).absoluteFilePath();
                    return true;
                }
                if(checkDateNext(year, month, day) )
                    return true;
            }

        }
        day = "0";

        if(month.toInt() < 12 && month.toInt() > -1){
            month = QString::number(month.toInt() + 1);

            if(month.toInt() < 10 && month.toInt() > 0)
                month.prepend("0");
            if(checkDateNext(year, month, day) )
                return true;
        }
    }
    year = QString::number(year.toInt() + 1);

    month = "0";

    if(checkDateNext(year, month, day) )
        return true;

    return false;
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
void SheduleDateSwitch::slotPreviosDay()
{
    emit signalPreviosDay(previosFileName);
}
void SheduleDateSwitch::slotNextDay()
{
    emit signalNextDay(nextFileName);
}
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
