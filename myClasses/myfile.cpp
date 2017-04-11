#include "myClasses/myfile.h"

bool MySpace::fileVerification(QFile *file, QString *filePath)
{
    if(!file->isOpen() && !file->open(QIODevice::ReadOnly) ){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(QString("Невозможно открыть файл: \"" + QFileInfo(*file).absoluteFilePath() ) + \
                       "\" для чтения");
        msgBox.exec();
        return false;
    }
    *filePath = QFileInfo(*file).absoluteFilePath();
    return true;
}
QDate MySpace::checkDate(QDate date, char operations)
{
    int day     = date.day();
    int month   = date.month();
    int year    = date.year();

    if(operations == '+'){
        day++;
        if(day > date.daysInMonth()){
            day = 1;
            month++;
            if(month > 12){
                month = 1;
                year++;
            }
        }
    }else if(operations == '-'){
        day--;
        if(day < 1){
            day = date.daysInMonth();
            month--;
            if(month < 1){
                month = 12;
                year--;
            }
        }
    }else
        printf("converter_main_table class error: argument \"operations\" is wrong!\n");

    QDate resultDate;
    resultDate.setDate(year, month, day);

    return resultDate;
}
