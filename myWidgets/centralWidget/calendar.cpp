#include "calendar.h"
#include "generalsettings.h"

#include <QDesktopWidget>
#include <QComboBox>
#include <QTextCharFormat>
#include <QDebug>

Calendar::Calendar() : QCalendarWidget()
{
    this->setGridVisible(true);

    this->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    this->setSelectionMode(QCalendarWidget::NoSelection);

    QComboBox headerTextFormatCombo;
    QString text = headerTextFormatCombo.currentText();
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    this->setHeaderTextFormat(format);

    this->setObjectName(OBJECT_NAME_CALENDAR);
}
Calendar::~Calendar()
{
    qDebug() << "Calender destruktor" ;
}
