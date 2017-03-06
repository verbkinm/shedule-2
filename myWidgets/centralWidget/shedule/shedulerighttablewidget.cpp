#include "shedulerighttablewidget.h"
#include "generalsettings.h"

#include <QStyleOption>
#include <QPainter>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>
#include <QHeaderView>

//CONSTRUKTOR
SheduleRightTableWidget::SheduleRightTableWidget(QWidget *parent) : QWidget(parent)
{
    pLayout = new QVBoxLayout;

    QFile file("out.xml");
    if(!file.open(QIODevice::ReadOnly) ){
        QMessageBox msgBox;
        msgBox.setText(QString("Невозможно открыть файл: " + QDir::currentPath() + PATH_SPLITER + QFileInfo(file).fileName()) );
        msgBox.exec();
        exit(1);
    }
    allFile = new QString(file.readAll());
    file.close();

    pDomDoc = new QDomDocument;
    pDomDoc->setContent(*allFile);

    //create DOMDOC
    structuring(pDomDoc);
    delete allFile; //???

    pTableWidget = new QTableWidget(numberOfRow,numberOfCollum);
    pTableWidget->horizontalHeader()->hide();
    pTableWidget->verticalHeader()->hide();

    pTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    pTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    pTableWidget->setEditTriggers(0);

    //CREATE QTABLE_ITEMS IN QTABLE_WIDGET
    for (int row = 0; row < numberOfRow; ++row)
        for (int column = 0; column < numberOfCollum; ++column) {
            pTableWidgetItem = new QTableWidgetItem;
            pTableWidget->setItem(row, column, pTableWidgetItem);
        }
    pTableWidget->item(0, 0)->setText("№");
    pTableWidget->item(0, 1)->setText("Время");
    //LESSON TIME AND NUMBER OF LESSONS
    for (int i = 1; i < numberOfRow; ++i){
        pTableWidget->item(i, 0)->setText(QString::number(i) );
        pTableWidget->item(i, 1)->setText(pArrLessonTime[i - 1]);
    }
    //NAME OF CLASS
    for (int i = 2; i < numberOfClass + 2; ++i)
        pTableWidget->item(0, i)->setText(tableShedule[0][i - 2].getHeader() );
    //FILLING CELLS
    for (int i = 1; i < numberOfRow; ++i)
        for (int ii = 2; ii < numberOfClass + 2; ++ii){
            pTableWidget->item(i, ii)->setText(tableShedule[i -1][ii - 2].getnameOfLesson() );
            QString currentText = pTableWidget->item(i, ii)->text();
            foreach (QString str, tableShedule[i -1][ii - 2].getTeachers()) {
                currentText.append("\n");
                currentText.append(str);
            }
            foreach (QString str, tableShedule[i -1][ii - 2].getRoomCabinets()) {
                currentText.append("\n");
                currentText.append(str);
            }
            pTableWidget->item(i, ii)->setText(currentText);
        }
    //ALIGN FIRST ROW
    for (int i = 0; i < numberOfCollum; ++i)
        pTableWidget->item(0, i)->setTextAlignment(Qt::AlignCenter);
    //ALIGN FIRST COLUMN
    for (int i = 1; i < numberOfRow; ++i)
        pTableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
    //SET FONT TABLE
    for (int i = 0; i < numberOfRow; ++i)
        for (int ii = 0; ii < numberOfCollum; ++ii) {
            QFont pFont(pTableWidget->item(i, ii)->font());
            pFont.setPixelSize(FONT_SIZE_TABLE_SHEDULE);
            pTableWidget->item(i, ii)->setFont(pFont);
        }
    pTableWidget->resizeColumnsToContents();
    pTableWidget->resizeRowsToContents();

    //FIXED SIZE COLUMN 0,1
    pTableWidget->setColumnWidth(0, 30);
    for (int i = 1; i < numberOfRow; ++i) {
        QString str = pTableWidget->item(i,1)->text();
        str.replace("-", "\n-\n");
        str.remove(" ");
        pTableWidget->item(i, 1)->setText(str);
        pTableWidget->item(i, 1)->setTextAlignment(Qt::AlignCenter);
    }
    pTableWidget->setColumnWidth(1, 40);
    //SET BOLD FONT AND BACKGROUND FOR 0-COLUMN
    for (int i = 0; i < numberOfCollum; ++i) {
        QFont font = pTableWidget->item(0, 1)->font();
        font.setBold(true);
        pTableWidget->item(0, i)->setFont(font);
        pTableWidget->item(0, i)->setBackgroundColor(QColor(228,228,228));
    }
    //SET BOLD FONT AND BACKGROUND FOR 0-ROW
    for (int i = 1; i < numberOfRow; ++i)
        for (int ii = 0; ii < 2; ++ii) {
            QFont font = pTableWidget->item(i, ii)->font();
            font.setBold(true);
            pTableWidget->item(i, ii)->setFont(font);
            pTableWidget->item(i, ii)->setBackgroundColor(QColor(228,228,228));
        }
    //SET BACKGOUND COLOR FOR I-ROW
    for (int i = 2; i < numberOfRow; i += 2)
        for (int ii = 2; ii < numberOfCollum; ++ii) {
            pTableWidget->item(i, ii)->setBackgroundColor(QColor(246,246,246));
        }

    pLayout->addWidget(pTableWidget);
    this->setLayout(pLayout);
}
//FUNCTIONS
void SheduleRightTableWidget::structuring(QDomDocument *pDomDoc)
{
    root            = pDomDoc->firstChild(); //<table>
    numberOfLesson  = root.childNodes().size() - 1;
    numberOfRow     = root.childNodes().size();
    numberOfCollum  = root.firstChild().childNodes().size();
    numberOfClass   = numberOfCollum - 2;
    pArrClassLiter  = new QString[numberOfClass];
    pArrLessonTime  = new QString[numberOfLesson];

    QDomNodeList nods = root.firstChild().childNodes();
    for (int i = 0; i < numberOfLesson; ++i)
        pArrLessonTime[i] = root.childNodes().at(i+1).childNodes().at(1).toElement().text();
    for (int i = 0; i < numberOfClass; ++i)
        pArrClassLiter[i] = nods.at(i+2).toElement().text();

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
}
//SLOTS
//EVENTS
void SheduleRightTableWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
//DECONSTRUKTOR
