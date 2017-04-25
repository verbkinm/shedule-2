#include "cell.h"

#include <QStringList>

#include <QDebug>

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
{
    this->header = header;
}
void Cell::setNameOfLesson(QString nameOfLesson)
{
    this->nameOfLesson = nameOfLesson.replace(" ","\n");
}
void Cell::setTeachers(QStringList teachers)
{
    for (QStringList::iterator it = teachers.begin(); it != teachers.end(); ++it){
        if(QString(*it).startsWith("/") ){
            teachers.erase(it);
            --it;
        }
    }

    this->teachers = teachers;

//    qDebug() << "setTEacher " << this->teachers;
}
void Cell::setRoomCabinets(QStringList roomCabinets)
{
    this->roomCabinets = roomCabinets;
}
QString Cell::getHeader()
{
    return header;
}
QString Cell::getnameOfLesson()
{
    return nameOfLesson;
}
QStringList Cell::getTeachers()
{
    return teachers;
}
QStringList Cell::getRoomCabinets()
{
    return roomCabinets;
}
