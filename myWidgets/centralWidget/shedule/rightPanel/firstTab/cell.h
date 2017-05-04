#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QColor>

class Cell : public QObject
{
    Q_OBJECT
private:
    QString         header; //цифра и буква класса
    QString         nameOfLesson;
    QStringList     teachers;
    QStringList     roomCabinets;

    bool            filtred;
    bool            currentLeson;

    QColor          background;

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

    void            setFiltred(bool value);
    bool            isFiltred();

    void            setCurrentLesson(bool value);
    bool            isCurrentLesson();

    void            setBackgroundColor(QColor color);
    QColor          backgroundColor();

signals:

public slots:
};

#endif // CELL_H
