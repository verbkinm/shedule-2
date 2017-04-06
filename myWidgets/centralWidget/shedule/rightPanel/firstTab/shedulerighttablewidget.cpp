#include "shedulerighttablewidget.h"
#include "../../shedule.h"
#include "generalsettings.h"
#include "../../../../converter_main_table_shedule.h"
#include "../../../../../myClasses/myfile.h"

#include <QStyleOption>
#include <QPainter>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>
#include <QHeaderView>
#include <QScrollBar>
#include <QDebug>
#include <QStringList>

//CONSTRUKTOR
SheduleRightTableWidget::SheduleRightTableWidget(QWidget *parent) : QWidget(parent)
{
    pFileSystemWatcher = new QFileSystemWatcher(this);
    file_is_exist_today = false;
    file_is_exist_yesterday = false;

    if(pFileSystemWatcher->addPath(SHARE_FILE_MAIN_SHEDULE_TODAY))
        file_is_exist_today = true;

    if(pFileSystemWatcher->addPath(SHARE_FILE_MAIN_SHEDULE_YESTERDAY))
        file_is_exist_yesterday = true;

    pFileSystemWatcher->addPath(SHARE_DIR_MAIN_SHEDULE_TODAY);
    pFileSystemWatcher->addPath(SHARE_DIR_MAIN_SHEDULE_YESTERDAY);

    pLayout = new QGridLayout;

    convert_html_and_creat_xml();
    createLeftTable();

    pLayout->addWidget(pTableRightHeader, 0,1);
    pLayout->addWidget(pTableWidgetLeft, 1,0);
    pLayout->addWidget(pTableWidget, 1,1);

    this->setLayout(pLayout);

    pTableWidgetItem = 0;

    connect(pFileSystemWatcher, SIGNAL(fileChanged(QString)),       this, SLOT(slotChangedFile(QString)) );
    connect(pFileSystemWatcher, SIGNAL(directoryChanged(QString)),  this, SLOT(slotChangedDir (QString)) );
}
//FUNCTIONS
void SheduleRightTableWidget::convert_html_and_creat_xml()
{
    Converter_main_table_shedule converterToday(SHARE_FILE_MAIN_SHEDULE_TODAY, LOCAL_FILE_MAIN_SHEDULE_TODAY);
    Converter_main_table_shedule converterYesterday(SHARE_FILE_MAIN_SHEDULE_YESTERDAY, LOCAL_FILE_MAIN_SHEDULE_YESTERDAY, true);

    QFile file(LOCAL_FILE_MAIN_SHEDULE_TODAY);
    if(!file.exists()){
        file.setFileName(QString(LOCAL_FILE_MAIN_SHEDULE_YESTERDAY));
        if(!file.exists()){
            QDir dir(LOCAL_ARCHIVE_PATH);
            if(dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot).size() == 0){
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.setText(QString("Невозможно открыть файл: \"" + QDir::currentPath() + PATH_SPLITER + QFileInfo(file).fileName()) + \
                               "\" или нет файлов в каталоге \"" + QDir::currentPath() + PATH_SPLITER + LOCAL_ARCHIVE_PATH + "\"" );
                msgBox.exec();
                exit(2);
            }
            bool break_all_foreach = false;
            foreach (QString str, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Reversed) ) {
                if(break_all_foreach) break;
                QDir dirYears(dir.absolutePath() + PATH_SPLITER + str);
                foreach (QString strMonthes, dirYears.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Reversed) ) {
                    if(break_all_foreach) break;
                    QDir dirMonthes(dirYears.absolutePath() + PATH_SPLITER + strMonthes);
                    foreach (QString strDays, dirMonthes.entryList(QDir::Files | QDir::NoDotAndDotDot, QDir::Reversed)) {
                        if(break_all_foreach) break;
                        file.setFileName(dirMonthes.absolutePath() + PATH_SPLITER + strDays);
                        if(fileVerification(&file, &currentFile))
                            break_all_foreach = true;
                    }
                }
            }
        }
    }
    fileVerification(&file, &currentFile);

    QString allTextInFile = file.readAll();
    file.close();

    QDomDocument domDoc;
    domDoc.setContent(allTextInFile);

    structuring(&domDoc);
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
//    pTableWidgetLeft->item(0, 0)->setText("№");
//    pTableWidgetLeft->item(0, 1)->setText("Время");
    //LESSON TIME AND NUMBER OF LESSONS
    for (int i = 0; i < numberOfRow; ++i){
        pTableWidgetLeft->item(i, 0)->setText(QString::number(i + 1) );
        pTableWidgetLeft->item(i, 1)->setText(pArrLessonTime[i]);
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
//    pTableWidgetLeft->setFixedHeight(500);
    pTableWidgetLeft->setMaximumHeight(fixedHeight + 2);

    connect(pTableWidget->verticalScrollBar(), SIGNAL(valueChanged(int)), pTableWidgetLeft->verticalScrollBar(), SLOT(setValue(int)) );
    emit signalSetDateSheduleDateSwitch(currentFile);
}
void SheduleRightTableWidget::createRightTable()
{
    pTableRightHeader = new QTableWidget(1, numberOfClass);
    pTableRightHeader->horizontalHeader()->hide();
    pTableRightHeader->verticalHeader()->hide();
    pTableRightHeader->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pTableRightHeader->setSelectionMode(QAbstractItemView::NoSelection);
    pTableRightHeader->setDragDropMode(QAbstractItemView::NoDragDrop);
    pTableRightHeader->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pTableRightHeader->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    pTableWidget = new QTableWidget(numberOfRow,numberOfClass);
    pTableWidget->horizontalHeader()->hide();
    pTableWidget->verticalHeader()->hide();
    pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    pTableWidget->setDragDropMode(QAbstractItemView::NoDragDrop);
    pTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    pTableWidget->setCurrentCell(0,0);

    //CREATE QTABLE_ITEMS IN pTableRightHeader
    for (int column = 0; column < numberOfCollum; ++column) {
        pTableWidgetItem = new QTableWidgetItem;
        pTableRightHeader->setItem(0,column, pTableWidgetItem);
    }
    //CREATE QTABLE_ITEMS IN pTableWidget
    for (int row = 0; row < numberOfRow; ++row)
        for (int column = 0; column < numberOfCollum; ++column) {
            pTableWidgetItem = new QTableWidgetItem;
            pTableWidget->setItem(row, column, pTableWidgetItem);
        }
    //NAME OF CLASS IN pTableRightHeader
    for (int i = 0; i < numberOfClass; ++i)
        pTableRightHeader->item(0, i)->setText(tableShedule[0][i].getHeader() );
    //FILLING CELLS IN pTableWidget
    for (int i = 0; i < numberOfRow; ++i)
        for (int ii = 0; ii < numberOfClass; ++ii){
            pTableWidget->item(i, ii)->setText(tableShedule[i][ii].getnameOfLesson() );
            QString currentText = pTableWidget->item(i, ii)->text();
            foreach (QString str, tableShedule[i][ii].getTeachers()) {
                currentText.append("\n");
                currentText.append(str);
            }
            foreach (QString str, tableShedule[i][ii].getRoomCabinets()) {
                currentText.append("\n");
                currentText.append(str);
            }
            pTableWidget->item(i, ii)->setText(currentText);
        }
    //SET FONT TABLE IN pTableWidget
    for (int i = 0; i < numberOfRow; ++i)
        for (int ii = 0; ii < numberOfClass; ++ii) {
            QFont pFont(pTableWidget->item(i, ii)->font());
            pFont.setPixelSize(FONT_SIZE_TABLE_SHEDULE);
            pTableWidget->item(i, ii)->setFont(pFont);
        }
    //ALIGN FIRST ROW IN pTableRightHeader
    for (int i = 0; i < numberOfClass; ++i)
        pTableRightHeader->item(0, i)->setTextAlignment(Qt::AlignCenter);
    //SET BOLD FONT AND BACKGROUND FOR 0-COLUMN IN pTableRightHeade
    for (int i = 0; i < numberOfClass; ++i) {
        pTableWidgetItem = pTableRightHeader->item(0, i);
        QFont font = pTableWidgetItem->font();
        font.setBold(true);
        pTableWidgetItem->setFont(font);
        pTableWidgetItem->setBackgroundColor(QColor(228,228,228));
    }
    pTableWidget->resizeColumnsToContents();
    pTableWidget->resizeRowsToContents();
    pTableRightHeader->resizeRowsToContents();

    //SET COLUMN WIDTH IN pTableRightHeader
    for (int column = 0; column < numberOfClass; ++column)
        pTableRightHeader->setColumnWidth(column, pTableWidget->columnWidth(column));
    //SET FIXED HEIGHT IN pTableRightHeader
    pTableRightHeader->setFixedHeight(pTableRightHeader->rowHeight(0));
    //SET BACKGOUND COLOR FOR I-ROW
    for (int i = 1; i < numberOfRow; i += 2)
        for (int ii = 0; ii < numberOfClass; ++ii)
            pTableWidget->item(i, ii)->setBackgroundColor(QColor(246,246,246));
    int fixedHeight = 0;
    for (int i = 0; i < numberOfRow; ++i)
        fixedHeight += pTableWidget->rowHeight(i);

    pTableWidget->setMaximumHeight(fixedHeight +2 );
}
void SheduleRightTableWidget::structuring(QDomDocument *pDomDoc)
{
    root            = pDomDoc->firstChild(); //<table>
    numberOfLesson  = root.childNodes().size() - 1;
    numberOfRow     = root.childNodes().size() - 1;
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
    connect(pTableWidget->horizontalScrollBar(), SIGNAL(valueChanged(int)), pTableRightHeader->horizontalScrollBar(), SLOT(setValue(int)) );
    return pTableWidget->horizontalScrollBar();
}
QScrollBar* SheduleRightTableWidget::getVerticalScroolBar()
{
    connect(pTableWidget->verticalScrollBar(), SIGNAL(valueChanged(int)), pTableRightHeader->verticalScrollBar(), SLOT(setValue(int)) );
    return pTableWidget->verticalScrollBar();
}
void SheduleRightTableWidget::setMaximumHeightTableWidget(int height)
{
    pTableWidget->setMaximumHeight(height);
}
void SheduleRightTableWidget::setMaximumHeightTableWidgetLeft(int height)
{
    pTableWidgetLeft->setMaximumHeight(height);
}
//SLOTS
void SheduleRightTableWidget::slotChangedFile(const QString &flName)
{
    if(flName.indexOf("сегодня") != -1){
        if(pFileSystemWatcher->addPath(SHARE_FILE_MAIN_SHEDULE_TODAY)){
            file_is_exist_today = true;
            delete pTableWidget;
            delete pTableWidgetLeft;
            convert_html_and_creat_xml();
            createLeftTable();
            pLayout->addWidget(pTableWidgetLeft, 0,0);
            pLayout->addWidget(pTableWidget, 0,1);
        }
        else
            file_is_exist_today = false;
    }
    if(flName.indexOf("завтра") != -1){
        if(pFileSystemWatcher->addPath(SHARE_FILE_MAIN_SHEDULE_YESTERDAY)){
            file_is_exist_yesterday = true;
            delete pTableWidget;
            delete pTableWidgetLeft;
            convert_html_and_creat_xml();
            createLeftTable();
            pLayout->addWidget(pTableWidgetLeft, 0,0);
            pLayout->addWidget(pTableWidget, 0,1);
        }
        else
            file_is_exist_yesterday = false;
    }
}
void SheduleRightTableWidget::slotChangedDir(const QString &dirName)
{
    if(dirName.indexOf("сегодня") != -1){
        QDir dir(SHARE_DIR_MAIN_SHEDULE_TODAY);
        if(!file_is_exist_today){
            foreach (QString str, dir.entryList(QDir::Files | QDir::NoDotAndDotDot)) {
                qDebug() << str;
                if(str == "izmenenie.html")
                    slotChangedFile(SHARE_FILE_MAIN_SHEDULE_TODAY);
            }
        }
    }
    if(dirName.indexOf("завтра") != -1){
        QDir dir(SHARE_DIR_MAIN_SHEDULE_YESTERDAY);
        if(!file_is_exist_yesterday){
            foreach (QString str, dir.entryList(QDir::Files | QDir::NoDotAndDotDot)) {
                if(str == "izmenenie.html")
                    slotChangedFile(SHARE_FILE_MAIN_SHEDULE_YESTERDAY);
            }
        }
    }
}
void SheduleRightTableWidget::slotRecreateTables(QString fileName)
{
    delete pTableRightHeader;
    delete pTableWidget;
    delete pTableWidgetLeft;

    QFile file(fileName);
    fileVerification(&file, &currentFile);

    QString allTextInFile = file.readAll();
    file.close();

    QDomDocument domDoc;
    domDoc.setContent(allTextInFile);

    structuring(&domDoc);

    createRightTable();
    createLeftTable();

    pLayout->addWidget(pTableRightHeader, 0,1);
    pLayout->addWidget(pTableWidgetLeft, 1,0);
    pLayout->addWidget(pTableWidget, 1,1);
}
//EVENTS
bool SheduleRightTableWidget::event(QEvent *event)
{
    if(this->isVisible() && event->type() == QEvent::Resize){
//        qDebug() << "resize" << pParent->size();
//        emit signalSetTableSize();
//        setUnits();
//        resized = 1;
    }
    return QWidget::event(event);
}
void SheduleRightTableWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
//DECONSTRUKTOR
SheduleRightTableWidget::~SheduleRightTableWidget()
{
    delete pFileSystemWatcher;
    delete pTableWidgetLeft;
//    if(pTableWidgetItem != 0)
//        delete pTableWidgetItem;
    delete pLayout;
    delete [] pArrClassLiter;
    delete [] pArrLessonTime;
//    delete [] tableShedule;
}
