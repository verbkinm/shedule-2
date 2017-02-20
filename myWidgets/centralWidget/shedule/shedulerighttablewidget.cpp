#include "shedulerighttablewidget.h"
#include "generalsettings.h"

#include <QFileInfo>
#include <QDir>
#include <QDebug>

SheduleRightTableWidget::SheduleRightTableWidget(QWidget *parent) : QWidget(parent)
{
    QFile file("out.xml");
    if(!file.open(QIODevice::ReadOnly) ){
        qDebug() << "Невозможно открыть файл" << QDir::currentPath() + PATH_SPLITER + QFileInfo(file).fileName();
        exit(1);
    }
    allFile = new QString(file.readAll());
    file.close();

    pDomDoc = new QDomDocument;
    pDomDoc->setContent(*allFile);

    structuring(pDomDoc);

}

void SheduleRightTableWidget::structuring(QDomDocument *pDomDoc)
{
    root            = pDomDoc->firstChild();
    numberOfLesson  = root.childNodes().size() - 1;
    numberOfCollum  = root.firstChild().childNodes().size();
    numberOfClass   = numberOfCollum - 2;
    pArrClassLiter  = new QString[numberOfClass];

    QDomNodeList nods= root.firstChild().childNodes();
    for (int i = 0; i < numberOfClass; ++i)
        pArrClassLiter[i] = nods.at(i+2).toElement().text();

    qDebug() << "numberOfLesson = " << numberOfLesson;
    qDebug() << "numberOfClass  = " << numberOfClass;

    tableShedule = new Cell*[numberOfClass];
    for (int i = 0; i < numberOfLesson; ++i) {
        tableShedule[i] = new Cell[numberOfClass];
        for (int j = 0; j < numberOfClass; ++j) {
            QString header      =  root.firstChild().childNodes().at(j+2).toElement().text();
            tableShedule[i][j].setHeader(header);
                                        //table       tr+1                   td+2                   table    tr                 td
            QString nameOfLesson =  root.childNodes().at(i+1).childNodes().at(j+2).firstChild().childNodes().at(0).childNodes().at(0).toElement().text();
            tableShedule[i][j].setNameOfLesson(nameOfLesson);

            QStringList teachers;
            QDomNodeList nodeList = root.childNodes().at(i+1).childNodes().at(j+2).firstChild().childNodes().at(0).childNodes();
            for (int ii = 1; ii < nodeList.size(); ++ii) {
                teachers << nodeList.at(ii).toElement().text();
                tableShedule[i][j].setTeachers(teachers);
            }

            QStringList roomCabinets;
            nodeList =              root.childNodes().at(i+1).childNodes().at(j+2).firstChild().childNodes().at(1).childNodes();
            for (int ii = 0; ii < nodeList.size(); ++ii) {
                roomCabinets << nodeList.at(ii).toElement().text();
                tableShedule[i][j].setRoomCabinets(roomCabinets);
            }
        }
    }
    for (int i = 0; i < numberOfLesson; ++i) {
        for (int j = 0; j < numberOfClass; ++j) {
            qDebug() << i+1 << pArrClassLiter[j] /*<< tableShedule[i][j].getHeader()*/ << tableShedule[i][j].getnameOfLesson() << \
                        tableShedule[i][j].getTeachers() << tableShedule[i][j].getRoomCabinets();

        }
    }

}
