#include "calendar.h"
#include <QDesktopWidget>
#include <QComboBox>
#include <QTextCharFormat>

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
}

