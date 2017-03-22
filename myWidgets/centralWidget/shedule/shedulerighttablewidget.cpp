#include "shedulerighttablewidget.h"
#include "shedule.h"
#include "generalsettings.h"

#include <QStyleOption>
#include <QPainter>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>
#include <QHeaderView>
#include <QScrollBar>
#include <QDebug>

//CONSTRUKTOR
SheduleRightTableWidget::SheduleRightTableWidget(QWidget *parent) : QWidget(parent)
{
    pFileSystemWatcher = new QFileSystemWatcher(this);
    file_is_exist = false;
    if(pFileSystemWatcher->addPath(SHARE_FILE_MAIN_SHEDULE_NAME))
        file_is_exist = true;
    pFileSystemWatcher->addPath(SHARE_DIR_MAIN_SHEDULE_NAME);
    pLayout = new QGridLayout;

    convert_html_and_creat_xml();

    createLeftTable();

    pLayout->addWidget(pTableWidgetLeft, 0,0);
    pLayout->addWidget(pTableWidget, 0,1);

    this->setLayout(pLayout);

    pTableWidgetItem = 0;

    connect(pFileSystemWatcher, SIGNAL(fileChanged(QString)),       this, SLOT(slotChangedFile(QString)) );
    connect(pFileSystemWatcher, SIGNAL(directoryChanged(QString)),  this, SLOT(slotChangedDir (QString)) );
    connect(pTableWidget->verticalScrollBar(), SIGNAL(valueChanged(int)), pTableWidgetLeft->verticalScrollBar(), SLOT(setValue(int)) );
}
//FUNCTIONS
void SheduleRightTableWidget::convert_html_and_creat_xml()
{
    pConverter_main_table_shedule = new Converter_main_table_shedule(SHARE_FILE_MAIN_SHEDULE_NAME, LOCAL_FILE_MAIN_SHEDULE_NAME,0);
    delete pConverter_main_table_shedule;

    QFile file("local"+QString(PATH_SPLITER)+"расписание уроков"+PATH_SPLITER+"на сегодня"+PATH_SPLITER+"сегодня.xml");
    if(!file.open(QIODevice::ReadOnly) ){
        QMessageBox msgBox;
        msgBox.setText(QString("Невозможно открыть файл: " + QDir::currentPath() + PATH_SPLITER + QFileInfo(file).fileName()) );
        msgBox.exec();
        exit(1);
    }
    allTextInFile = new QString(file.readAll());
    file.close();

    pDomDoc = new QDomDocument;
    pDomDoc->setContent(*allTextInFile);

    //create DOMDOC
    structuring(pDomDoc);
    delete allTextInFile; //???

    createRightTable();
}

void SheduleRightTableWidget::createLeftTable()
{
    pTableWidgetLeft = new QTableWidget(numberOfRow,2);
    pTableWidgetLeft->horizontalHeader()->hide();
    pTableWidgetLeft->verticalHeader()->hide();

//    pTableWidgetLeft->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pTableWidgetLeft->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pTableWidgetLeft->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pTableWidgetLeft->setSelectionMode(QAbstractItemView::NoSelection);
    pTableWidgetLeft->setDragDropMode(QAbstractItemView::NoDragDrop);

    //CREATE QTABLE_ITEMS IN QTABLE_WIDGET
    for (int row = 0; row < numberOfRow; ++row)
        for (int column = 0; column < 2; ++column) {
            pTableWidgetItem = new QTableWidgetItem;
            pTableWidgetLeft->setItem(row, column, pTableWidgetItem);
            pTableWidgetItem->setTextAlignment(Qt::AlignCenter);
        }
    pTableWidgetLeft->item(0, 0)->setText("№");
    pTableWidgetLeft->item(0, 1)->setText("Время");
    //LESSON TIME AND NUMBER OF LESSONS
    for (int i = 1; i < numberOfRow; ++i){
        pTableWidgetLeft->item(i, 0)->setText(QString::number(i) );
        pTableWidgetLeft->item(i, 1)->setText(pArrLessonTime[i - 1]);
    }
    //FIXED SIZE COLUMN 0,1
    pTableWidgetLeft->setColumnWidth(0, 30);
    for (int i = 1; i < numberOfRow; ++i) {
        QString str = pTableWidgetLeft->item(i,1)->text();
        str.remove(" ");
        str.replace("-", "\n-\n");
        pTableWidgetLeft->item(i, 1)->setText(str);
    }
    pTableWidgetLeft->setColumnWidth(1, 40);
    //SET BOLD FONT AND BACKGROUND FOR 0-COLUMN
    for (int i = 0; i < 2; ++i) {
        pTableWidgetItem = pTableWidgetLeft->item(0, i);
        QFont font = pTableWidgetItem->font();
        font.setBold(true);
        pTableWidgetItem->setFont(font);
        pTableWidgetItem->setBackgroundColor(QColor(228,228,228));
    }
    //SET FONT TABLE
    for (int i = 0; i < numberOfRow; ++i)
        for (int ii = 0; ii < 2; ++ii) {
            QFont pFont(pTableWidgetLeft->item(i, ii)->font());
            pFont.setPixelSize(FONT_SIZE_TABLE_SHEDULE);
            pTableWidgetLeft->item(i, ii)->setFont(pFont);
        }
    //SET BOLD FONT AND BACKGROUND FOR 0-ROW
    for (int i = 1; i < numberOfRow; ++i)
        for (int ii = 0; ii < 2; ++ii) {
            pTableWidgetItem = pTableWidgetLeft->item(i, ii);
            QFont font = pTableWidgetItem->font();
            font.setBold(true);
            pTableWidgetItem->setFont(font);
            pTableWidgetItem->setBackgroundColor(QColor(228,228,228));
        }
    for (int i = 0; i < numberOfRow; ++i)
        pTableWidgetLeft->setRowHeight(i,pTableWidget->rowHeight(i));

    pTableWidgetLeft->setFixedWidth(pTableWidgetLeft->columnWidth(0) + pTableWidgetLeft->columnWidth(1) + 2);
    int fixedHeight = 0;
    for (int i = 0; i < numberOfRow; ++i)
        fixedHeight += pTableWidgetLeft->rowHeight(i);
    pTableWidgetLeft->setFixedHeight(500);
//    pTableWidgetLeft->setMaximumHeight(fixedHeight + 2);
}
void SheduleRightTableWidget::createRightTable()
{
    pTableWidget = new QTableWidget(numberOfRow,numberOfClass);
    pTableWidget->horizontalHeader()->hide();
    pTableWidget->verticalHeader()->hide();
    pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    pTableWidget->setDragDropMode(QAbstractItemView::NoDragDrop);
    pTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    pTableWidget->setCurrentCell(0,0);

    //CREATE QTABLE_ITEMS IN QTABLE_WIDGET
    for (int row = 0; row < numberOfRow; ++row)
        for (int column = 0; column < numberOfCollum; ++column) {
            pTableWidgetItem = new QTableWidgetItem;
            pTableWidget->setItem(row, column, pTableWidgetItem);
        }
    //NAME OF CLASS
    for (int i = 0; i < numberOfClass; ++i)
        pTableWidget->item(0, i)->setText(tableShedule[0][i].getHeader() );
    //FILLING CELLS
    for (int i = 1; i < numberOfRow; ++i)
        for (int ii = 0; ii < numberOfClass; ++ii){
            pTableWidget->item(i, ii)->setText(tableShedule[i -1][ii].getnameOfLesson() );
            QString currentText = pTableWidget->item(i, ii)->text();
            foreach (QString str, tableShedule[i -1][ii].getTeachers()) {
                currentText.append("\n");
                currentText.append(str);
            }
            foreach (QString str, tableShedule[i -1][ii].getRoomCabinets()) {
                currentText.append("\n");
                currentText.append(str);
            }
            pTableWidget->item(i, ii)->setText(currentText);
        }
    //ALIGN FIRST ROW
    for (int i = 0; i < numberOfClass; ++i)
        pTableWidget->item(0, i)->setTextAlignment(Qt::AlignCenter);
    //SET FONT TABLE
    for (int i = 0; i < numberOfRow; ++i)
        for (int ii = 0; ii < numberOfClass; ++ii) {
            QFont pFont(pTableWidget->item(i, ii)->font());
            pFont.setPixelSize(FONT_SIZE_TABLE_SHEDULE);
            pTableWidget->item(i, ii)->setFont(pFont);
        }
    pTableWidget->resizeColumnsToContents();
    pTableWidget->resizeRowsToContents();
    //SET BOLD FONT AND BACKGROUND FOR 0-COLUMN
    for (int i = 0; i < numberOfClass; ++i) {
        pTableWidgetItem = pTableWidget->item(0, i);
        QFont font = pTableWidgetItem->font();
        font.setBold(true);
        pTableWidgetItem->setFont(font);
        pTableWidgetItem->setBackgroundColor(QColor(228,228,228));
    }
    //SET BACKGOUND COLOR FOR I-ROW
    for (int i = 2; i < numberOfRow; i += 2)
        for (int ii = 0; ii < numberOfClass; ++ii)
            pTableWidget->item(i, ii)->setBackgroundColor(QColor(246,246,246));
    int fixedHeight = 0;
    for (int i = 0; i < numberOfRow; ++i)
        fixedHeight += pTableWidget->rowHeight(i);

    pTableWidget->setMaximumHeight(fixedHeight);
}
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
QScrollBar* SheduleRightTableWidget::getHorizontalScroolBar()
{
    return pTableWidget->horizontalScrollBar();
}

//SLOTS
void SheduleRightTableWidget::slotChangedFile(const QString &flName)
{
    qDebug() << "file" << flName;
    if(pFileSystemWatcher->addPath(SHARE_FILE_MAIN_SHEDULE_NAME))
        file_is_exist = true;
    else
        file_is_exist = false;
//    delete pTableWidget;
//    convert_html_and_creat_xml();
//    pLayout->addWidget(pTableWidget, 0,1);
}
void SheduleRightTableWidget::slotChangedDir(const QString &dirName)
{
    qDebug() << "dir" << dirName;
//    pFileSystemWatcher->addPath(SHARE_DIR_MAIN_SHEDULE_NAME);
    QDir dir(SHARE_DIR_MAIN_SHEDULE_NAME);
    if(!file_is_exist){
        foreach (QString str, dir.entryList()) {
            if(str == "izmenenie.html")
                slotChangedFile(0);
        }
    }
}

//EVENTS
void SheduleRightTableWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
//DECONSTRUKTOR
