#include "cell.h"

#include <QStringList>

Cell::Cell(QString header, QString nameOfLesson, QStringList teachers, QStringList roomCabinets) : QObject()
{
    setHeader(header);
    setNameOfLesson(nameOfLesson);
    setTeachers(teachers);
    setRoomCabinets(roomCabinets);
}
Cell::Cell() : QObject()
{

}

void Cell::setHeader(QString header)
{this->header = header;}
void Cell::setNameOfLesson(QString nameOfLesson)
{
    this->nameOfLesson = nameOfLesson.replace(" ","\n");
}
void Cell::setTeachers(QStringList teachers)
{
    for (int i = 0; i < teachers.size(); ++i)
        if(QString(teachers.at(i)).startsWith("/") )
            teachers.removeAt(i);
    this->teachers = teachers;
}
void Cell::setRoomCabinets(QStringList roomCabinets)
{this->roomCabinets = roomCabinets;}

QString Cell::getHeader()
{return header;}
QString Cell::getnameOfLesson()
{return nameOfLesson;}
QStringList Cell::getTeachers()
{return teachers;}
QStringList Cell::getRoomCabinets()
{return roomCabinets;}
