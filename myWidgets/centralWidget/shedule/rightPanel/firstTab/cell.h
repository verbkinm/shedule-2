#ifndef CELL_H
#define CELL_H

#include <QObject>

class Cell : public QObject
{
    Q_OBJECT
private:
    QString         header; //цифра и буква класса
    QString         nameOfLesson;
    QStringList     teachers;
    QStringList     roomCabinets;

public:
    Cell(QString header, QString nameOfLesson, QStringList teachers, QStringList roomCabinets);
    Cell();

    void            setHeader       (QString header);
    void            setNameOfLesson (QString nameOfLesson);
    void            setTeachers     (QStringList teachers);
    void            setRoomCabinets (QStringList roomCabinets);

    QString         getHeader       ();
    QString         getnameOfLesson ();
    QStringList     getTeachers     ();
    QStringList     getRoomCabinets ();

signals:

public slots:
};

#endif // CELL_H
