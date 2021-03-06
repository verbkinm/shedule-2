#include "sheduletablewidget.h"
#include "../../shedule.h"
#include "generalsettings.h"
#include "../../../../converter_main_table_shedule.h"
#include "../../../../../myClasses/myfile.h"
#include "../../inherited/myfilter.h"

#include <QStyleOption>
#include <QPainter>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>
#include <QHeaderView>
#include <QScrollBar>
#include <QDebug>
#include <QStringList>
#include <QString>
#include <QMessageBox>
#include <QStringList>

//CONSTRUKTOR
SheduleTableWidget::SheduleTableWidget(QWidget *parent) : QWidget(parent)
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
    createRightTable();
    createLeftTable();
    createSheduleDateSwitch();

    pLayout->addWidget(new QWidget,         0,0, 1,3); //spacing
    pLayout->addWidget(pTableRightHeader,   1,1);
    pLayout->addWidget(pTableWidgetLeft,    2,0);
    pLayout->addWidget(pTableWidget,        2,1);

    pLayout->addWidget(pScrollVertical,     1,2, 2,1);
    pLayout->addWidget(pScrollHorizontal,   3,0, 1,3);
    pLayout->addWidget(pSheduleDateSwitch,  4,0, 1,3);
    pLayout->addWidget(new QWidget,         5,0, 1,3); //spacing

    pScrollHorizontal->setFixedHeight(SCROLL_BAR_WIDTH);
    pScrollVertical->setFixedWidth(SCROLL_BAR_WIDTH);

    this->setLayout(pLayout);

    pTableWidgetItem = 0;

    connect(pFileSystemWatcher, SIGNAL(fileChanged(QString)),       this, SLOT(slotChangedFile(QString)) );
    connect(pFileSystemWatcher, SIGNAL(directoryChanged(QString)),  this, SLOT(slotChangedDir (QString)) );
}

//FUNCTIONS
void SheduleTableWidget::convert_html_and_creat_xml()
{
    Converter_main_table_shedule converterToday(SHARE_FILE_MAIN_SHEDULE_TODAY);
//    Converter_main_table_shedule converterYesterday(SHARE_FILE_MAIN_SHEDULE_YESTERDAY, true);

    QFile file;

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
    QRegExp regExprYears("\\d\\d\\d\\d");
    QRegExp regExprMonths("\\d\\d");
    QRegExp regExprDays("\\d\\d.xml");
    //проверяем папку архива на содержание подпапок (папок года)
    foreach (QString strArchive, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Reversed) ) {
        if(break_all_foreach)
            break;
        if(!regExprYears.exactMatch(strArchive))
            continue;
        QDir dirYears(dir.absolutePath() + PATH_SPLITER + strArchive);
        //проверяем папку года на содержание подпапок (месяцев)
        foreach (QString strMonthes, dirYears.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Reversed) ) {
            if(break_all_foreach) break;
            if(!regExprMonths.exactMatch(strMonthes))
                continue;
            QDir dirMonthes(dirYears.absolutePath() + PATH_SPLITER + strMonthes);
            //проверяем папку месяца на содержание файлов
            foreach (QString strDays, dirMonthes.entryList(QDir::Files | QDir::NoDotAndDotDot, QDir::Reversed)) {
                if(break_all_foreach) break;
                if(!regExprDays.exactMatch(strDays))
                    continue;
                file.setFileName(dirMonthes.absolutePath() + PATH_SPLITER + strDays);
                if(MySpace::fileVerification(&file, &currentFile))
                    break_all_foreach = true;
            }
        }
    }
    qDebug() << QFileInfo(file).absoluteFilePath();
    MySpace::fileVerification(&file, &currentFile);

    QString allTextInFile = file.readAll();
    file.close();

    QDomDocument domDoc;
    domDoc.setContent(allTextInFile);

    structuring(&domDoc);
}
void SheduleTableWidget::createSheduleDateSwitch()
{
    pSheduleDateSwitch       = new SheduleDateSwitch;
    slotSetDate(currentFile);

    connect(pSheduleDateSwitch, SIGNAL(signalPreviosDay(QString)),this, SLOT(slotRecreateTables(QString)) );
    connect(pSheduleDateSwitch, SIGNAL(signalNextDay(QString)),   this, SLOT(slotRecreateTables(QString)) );
    connect(pSheduleDateSwitch, SIGNAL(signalToday(QString)),     this, SLOT(slotRecreateTables(QString)) );
}
void SheduleTableWidget::createLeftTable()
{
    pTableWidgetLeft = new QTableWidget(numberOfRow,2,this);
        pTableWidgetLeft->horizontalHeader()->hide();
        pTableWidgetLeft->verticalHeader()->hide();

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
    pTableWidgetLeft->setMaximumHeight(fixedHeight + 2);

    connect(pTableWidget->verticalScrollBar(), SIGNAL(valueChanged(int)), pTableWidgetLeft->verticalScrollBar(), SLOT(setValue(int)) );
    connect(&timerForslotSetBackgroundCurrentLesson, SIGNAL(timeout()), this, SLOT(slotSetBackgroundCurrentLesson()) );
        timerForslotSetBackgroundCurrentLesson.start(1000);
    connect(this, SIGNAL(signalChangeCurrentLesson(int)), this, SLOT(slotChangeCurrentLesson(int)) );
}
void SheduleTableWidget::createRightTable()
{
    pTableRightHeader = new QTableWidget(1, numberOfClass,this);
    pTableRightHeader->horizontalHeader()->hide();
    pTableRightHeader->verticalHeader()->hide();
    pTableRightHeader->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pTableRightHeader->setSelectionMode(QAbstractItemView::NoSelection);
    pTableRightHeader->setDragDropMode(QAbstractItemView::NoDragDrop);
    pTableRightHeader->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pTableRightHeader->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    pTableWidget = new QTableWidget(numberOfRow,numberOfClass,this);
    pTableWidget->installEventFilter(this);

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
    for (int i = 0; i < numberOfRow; ++i){
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
            pTableWidget->item(i, ii)->setBackgroundColor(DEFAULT_BACKGROUND_COLOR);
        }
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
    //SET BOLD FONT AND BACKGROUND FOR 0-COLUMN IN pTableRightHeader
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
    for (int i = 1; i < numberOfRow; i += 2){
        for (int ii = 0; ii < numberOfClass; ++ii){
            pTableWidget->item(i, ii)->setBackgroundColor(NOT_EVEN_ROW_COLOR);
            tableShedule[i][ii].setBackgroundColor(NOT_EVEN_ROW_COLOR);
        }
    }
    int fixedHeight = 0;
    int fixedWidth  = 0;
    for (int i = 0; i < numberOfRow; ++i)
        fixedHeight += pTableWidget->rowHeight(i);
    for (int i = 0; i < numberOfCollum; ++i)
        fixedWidth += pTableWidget->columnWidth(i);

    pTableWidget->setMaximumHeight(fixedHeight +2 );
    pScrollVertical = pTableWidget->verticalScrollBar();
    connect(pScrollVertical, SIGNAL(valueChanged(int)), this, SLOT(slotArrowsVisible()) );

    pScrollHorizontal = pTableWidget->horizontalScrollBar();
    connect(pScrollHorizontal, SIGNAL(valueChanged(int)), pTableRightHeader->horizontalScrollBar(), SLOT(setValue(int)) );
    connect(pScrollHorizontal, SIGNAL(valueChanged(int)), this, SLOT(slotArrowsVisible()) );

    pMyTouchScreen = new MyTouchScreen(pTableWidget);
    pMyTouchScreen->resize(fixedWidth, fixedHeight);

    connect(pMyTouchScreen, SIGNAL(signalChangeX(int)), this, SLOT(slotMyScreenValueChanchedX(int)) );
    connect(pMyTouchScreen, SIGNAL(signalChangeY(int)), this, SLOT(slotMyScreenValueChanchedY(int)) );

    for (signed int i = 0; i < (signed)(sizeof(arrArrow) / sizeof(arrArrow[0])); ++i)
        arrArrow[i] = new QLabel(pTableWidget);
}
void SheduleTableWidget::structuring(QDomDocument *pDomDoc)
{
    root            = pDomDoc->firstChild(); //<table>
    numberOfLesson  = root.childNodes().size() - 1;
    numberOfRow     = root.childNodes().size() - 1;
    numberOfCollum  = root.firstChild().childNodes().size();
    numberOfClass   = numberOfCollum - 2;
    if(numberOfClass < 1){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(QString("class SheduleTableWidget, function structuring(QDomDocument *pDomDoc) \
                        variable numberOfClass, value < 1 " + QString::number(numberOfClass)) );
        msgBox.exec();
        exit(6);
    }
    pArrClassLiter  = new QString[numberOfClass];
    pArrLessonTime  = new QString[numberOfLesson];

    QDomNodeList nods = root.firstChild().childNodes();
    for (int i = 0; i < numberOfLesson; ++i)
        pArrLessonTime[i] = root.childNodes().at(i+1).childNodes().at(1).toElement().text();
    for (int i = 0; i < numberOfClass; ++i)
        pArrClassLiter[i] = nods.at(i+2).toElement().text();

    tableShedule = new Cell*[numberOfLesson];


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
            tableShedule[i][j].setBackgroundColor(DEFAULT_BACKGROUND_COLOR);
        }
    }
}
void SheduleTableWidget::setMaximumHeightTableWidget(int height)
{
    pTableWidget->setMaximumHeight(height);
}
void SheduleTableWidget::setMaximumHeightTableWidgetLeft(int height)
{
    pTableWidgetLeft->setMaximumHeight(height);
}
void SheduleTableWidget::setFilter(const QString *filterLesson, const QString *filterTeacher)
{
    lessonFilter = filterLesson->toUpper().remove(":").remove(" ");
    teacherFilter= filterTeacher->toUpper().remove(":").remove(" ").remove(".");

    QString     originLesson;
    QStringList originalTeachers;

    itemsList.clear();

    for (int i = 0; i < numberOfRow; ++i){
        for (int ii = 0; ii < numberOfClass; ++ii){
            originLesson = tableShedule[i][ii].getnameOfLesson().remove("\n").remove(" ").toUpper();
            originalTeachers = tableShedule[i][ii].getTeachers();
            for (QStringList::iterator it = originalTeachers.begin(); it != originalTeachers.end(); ++it)
                *it = QString(*it).toUpper().remove(" ").remove(".");

            if( (originLesson == lessonFilter) && isStringInList(originalTeachers, teacherFilter) && lessonFilter != ""){
                pTableWidget->item(i, ii)->setBackgroundColor(FILTRED_CELL);
                tableShedule[i][ii].setFiltred(true);
                itemsList << pTableWidget->item(i, ii);
            }
            else{
                if(tableShedule[i][ii].isCurrentLesson())
                    pTableWidget->item(i, ii)->setBackgroundColor(BACKGROUND_COLOR_CURRENT_LESSON);
                else
                    pTableWidget->item(i, ii)->setBackgroundColor(tableShedule[i][ii].backgroundColor());

                tableShedule[i][ii].setFiltred(false);
            }
        }
    }
    slotArrowsVisible();
//    slotSetBackgroundCurrentLesson();
}
bool SheduleTableWidget::isStringInList(QStringList list, QString string)
{
    foreach (QString it, list) {
        if(it.startsWith(string))
            return true;
    }
    return false;
}
void SheduleTableWidget::set_cell(cell *myCell, bool visibleX, bool visibleY, bool left, bool top, bool right, bool bottom)
{
    myCell->visibleX = visibleX;
    myCell->visibleY = visibleY;
    myCell->left     = left;
    myCell->top      = top;
    myCell->right    = right;
    myCell->bottom   = bottom;
}
SheduleTableWidget::cell SheduleTableWidget::isCellInSight(QTableWidget *table, QTableWidgetItem *item)
{
    cell tmpCell;
    set_cell(&tmpCell, false, false, false, false, false, false);

    QRect rect = table->visualItemRect(item);
    //X
    if( (rect.x() + rect.width() > table->viewport()->width() ) ){
        set_cell(&tmpCell, false,false,   false,        tmpCell.top,  true,           tmpCell.bottom); // right
    }
    if( rect.x() < 0 )
        set_cell(&tmpCell, false,false,   true,         tmpCell.top,  false,          tmpCell.bottom); // left
    if( (rect.x() > 0) && (rect.x() + rect.width() < table->viewport()->width()) )
        set_cell(&tmpCell, true,false,    tmpCell.left, tmpCell.top,  tmpCell.right,  tmpCell.bottom); // visible_X

    //Y
    if( rect.y() + rect.height() > table->viewport()->height() )
        set_cell(&tmpCell, tmpCell.visibleX,false,   tmpCell.left, false,        tmpCell.right,  true); // bottom
    if( rect.y() < 0 ){
        set_cell(&tmpCell, tmpCell.visibleX,false,   tmpCell.left, true,         tmpCell.right,  false); // top
    }
    if( rect.y() > 0 && rect.y() + rect.height() < table->viewport()->height() )
        set_cell(&tmpCell, tmpCell.visibleX,true,    tmpCell.left, false,        tmpCell.right,  false); // visible_y

    return tmpCell;
}
void SheduleTableWidget::creatArrowsForTable()
{
    QPixmap pix;

    for (signed int i = 0; i < (signed)(sizeof(arrArrow) / sizeof(arrArrow[0])); ++i) {
        pix.load(":/img/arrow_"+QString::number(i+1));
        arrArrow[i]->setFixedSize(30,30);
        arrArrow[i]->setPixmap(pix.scaled(30,30 ,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    int width  = arrArrow[0]->width();
    int height = arrArrow[0]->height();
    arrArrow[0]->move(0,0);
    arrArrow[1]->move(pTableWidget->width() / 2 - width,0);
    arrArrow[2]->move(pTableWidget->width() - width,0);
    arrArrow[3]->move(0,pTableWidget->height() / 2 - height / 2);
    arrArrow[4]->move(pTableWidget->width() - width,pTableWidget->height() / 2 - height / 2);
    arrArrow[5]->move(0,pTableWidget->height() - height);
    arrArrow[6]->move(pTableWidget->width() / 2 - width,pTableWidget->height() - height);
    arrArrow[7]->move(pTableWidget->width() - width,pTableWidget->height() - height);

    for (signed int i = 0; i < (signed)(sizeof(arrArrow) / sizeof(arrArrow[0])); ++i)
        arrArrow[i]->hide();
}

//SLOTS
void SheduleTableWidget::slotMyScreenValueChanchedX(int x)
{
    pScrollHorizontal->setValue(pScrollHorizontal->value() + x);
    slotArrowsVisible();
}
void SheduleTableWidget::slotMyScreenValueChanchedY(int y)
{
    pScrollVertical->setValue(pScrollVertical->value() + y);
    slotArrowsVisible();
}
void SheduleTableWidget::slotSetDate(QString date)
{
    pSheduleDateSwitch->setSheduleDateSwitchText(date);
}
void SheduleTableWidget::slotChangedFile(const QString &flName)
{
    if(flName.indexOf("сегодня") != -1){
        if(pFileSystemWatcher->addPath(SHARE_FILE_MAIN_SHEDULE_TODAY)){
            file_is_exist_today = true;
//            delete pTableRightHeader;
//            delete pTableWidget;
//            delete pTableWidgetLeft;
            convert_html_and_creat_xml();
//            createLeftTable();
//            pLayout->addWidget(pTableRightHeader,   1,1);
//            pLayout->addWidget(pTableWidgetLeft,    2,0);
//            pLayout->addWidget(pTableWidget,        2,1);
//            emit pSheduleDateSwitch->signalToday(currentFile);
        }
        else
            file_is_exist_today = false;
    }
    if(flName.indexOf("завтра") != -1){
        if(pFileSystemWatcher->addPath(SHARE_FILE_MAIN_SHEDULE_YESTERDAY)){
            file_is_exist_yesterday = true;
//            delete pTableRightHeader;
//            delete pTableWidget;
//            delete pTableWidgetLeft;
//            convert_html_and_creat_xml();
//            createLeftTable();
//            pLayout->addWidget(pTableRightHeader,   1,1);
//            pLayout->addWidget(pTableWidgetLeft,    2,0);
//            pLayout->addWidget(pTableWidget,        2,1);
            emit pSheduleDateSwitch->signalNextDay(currentFile);
        }
        else
            file_is_exist_yesterday = false;
    }
}
void SheduleTableWidget::slotChangedDir(const QString &dirName)
{
    if(dirName.indexOf("сегодня") != -1){
        QDir dir(dirName);
        qDebug() << "slotChangeDir сегодня";
        if(!file_is_exist_today){
            foreach (QString str, dir.entryList(QDir::Files | QDir::NoDotAndDotDot)) {
                if(str == "izmenenie.html")
                    convert_html_and_creat_xml();
//                    slotChangedFile(SHARE_FILE_MAIN_SHEDULE_TODAY);
            }
        }
    }
    if(dirName.indexOf("завтра") != -1){
        QDir dir(SHARE_DIR_MAIN_SHEDULE_YESTERDAY);
        if(!file_is_exist_yesterday){
            foreach (QString str, dir.entryList(QDir::Files | QDir::NoDotAndDotDot)) {
                if(str == "izmenenie.html"){
                    slotChangedFile(SHARE_FILE_MAIN_SHEDULE_YESTERDAY);
                }
            }
        }
    }
}
void SheduleTableWidget::slotRecreateTables(QString fileName)
{
    for (int i = 0; i < numberOfLesson; ++i)
        delete []tableShedule[i];
    delete []tableShedule;

    delete pTableRightHeader;
    delete pTableWidget;
    delete pTableWidgetLeft;
    delete pSheduleDateSwitch;

    delete pScrollHorizontal;
    delete pScrollVertical;

    itemsList.clear();

    QFile file(fileName);
    if(!MySpace::fileVerification(&file, &currentFile) )
        return;

    QString allTextInFile = file.readAll();
    file.close();

    QDomDocument domDoc;
    domDoc.setContent(allTextInFile);

    structuring(&domDoc);

    createRightTable();
    createLeftTable();
    createSheduleDateSwitch();

    pLayout->addWidget(pTableRightHeader,   1,1);
    pLayout->addWidget(pTableWidgetLeft,    2,0);
    pLayout->addWidget(pTableWidget,        2,1);

    pLayout->addWidget(pScrollVertical,     1,2, 2,1);
    pLayout->addWidget(pScrollHorizontal,   3,0, 1,3);

    pLayout->addWidget(pSheduleDateSwitch,  4,0, 1,3);

    pScrollHorizontal->setFixedHeight(SCROLL_BAR_WIDTH);
    pScrollVertical->setFixedWidth(SCROLL_BAR_WIDTH);

    setFilter(&lessonFilter, &teacherFilter);
}
void SheduleTableWidget::slotArrowsVisible()
{
    for (signed int i = 0; i < (signed)(sizeof(arrArrow) / sizeof(arrArrow[0])); ++i)
        arrArrow[i]->hide();

    foreach (QTableWidgetItem* item, itemsList) {
        cell buffCell = isCellInSight(pTableWidget, item);

        if(buffCell.left && !buffCell.bottom && buffCell.top && !buffCell.right)
            arrArrow[0]->setVisible(true); // nw (0)
        if(!buffCell.left && !buffCell.bottom && buffCell.top && !buffCell.right)
            arrArrow[1]->setVisible(true); // n (1)
        if(!buffCell.left && !buffCell.bottom && buffCell.top && buffCell.right)
            arrArrow[2]->setVisible(true); // ne(2)

        if(buffCell.left && !buffCell.bottom && !buffCell.top && !buffCell.right)
            arrArrow[3]->setVisible(true); // west (3)
        if(!buffCell.left && !buffCell.bottom && !buffCell.top && buffCell.right)
            arrArrow[4]->setVisible(true); // east (4)

        if(buffCell.left && buffCell.bottom && !buffCell.top && !buffCell.right)
            arrArrow[5]->setVisible(true); // sw (5)
        if(!buffCell.left && buffCell.bottom && !buffCell.top && !buffCell.right)
            arrArrow[6]->setVisible(true); // s (6)
        if(!buffCell.left && buffCell.bottom && !buffCell.top && buffCell.right)
            arrArrow[7]->setVisible(true); // se (7)
    }
}
void SheduleTableWidget::slotSetBackgroundCurrentLesson()
{
    QTime beginLesson, endLesson, currenTime;
    currenTime = QTime::currentTime();

    for (int i = 0; i < numberOfLesson; ++i) {
        QStringList list = pArrLessonTime[i].remove(" ").split("-");
        beginLesson.setHMS(QString(list.at(0)).mid(0,2).toInt(), QString(list.at(0)).mid(3,2).toInt(),0);
        endLesson.setHMS(QString(list.at(1)).mid(0,2).toInt(), QString(list.at(1)).mid(3,2).toInt(),0);
        if(MySpace::inTheTimeInterval(beginLesson, endLesson, currenTime)){
            emit signalChangeCurrentLesson(i);
            for (int ii = 0; ii < numberOfClass; ++ii) {
                pTableWidgetItem = pTableWidget->item(i, ii);
                if(!tableShedule[i][ii].isFiltred() && !tableShedule[i][ii].isCurrentLesson()){
                    pTableWidgetItem->setBackgroundColor(BACKGROUND_COLOR_CURRENT_LESSON);
                    tableShedule[i][ii].setCurrentLesson(true);
                }
            }
        }
        else
            emit signalChangeCurrentLesson(-1);
    }
}
void SheduleTableWidget::slotChangeCurrentLesson(int lesson)
{
    for (int i = 0; i < numberOfLesson; ++i) {
        if(i == lesson)
            continue;
        for (int ii = 0; ii < numberOfClass; ++ii) {
            pTableWidgetItem = pTableWidget->item(i, ii);
            if(!tableShedule[i][ii].isFiltred() && pTableWidgetItem->backgroundColor() == BACKGROUND_COLOR_CURRENT_LESSON ){
                pTableWidgetItem->setBackgroundColor(tableShedule[i][ii].backgroundColor());
            }
            tableShedule[i][ii].setCurrentLesson(false);
        }
    }
}

//EVENTS
bool SheduleTableWidget::event(QEvent *event)
{

    return QWidget::event(event);
}
bool SheduleTableWidget::eventFilter(QObject *obj, QEvent *event)
{
//    qDebug() << event->type();
    if(pTableWidget->isVisible() && event->type() == QEvent::Resize){
        creatArrowsForTable();
        slotArrowsVisible();
    }

    return QObject::eventFilter(obj, event);
}

void SheduleTableWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

//DECONSTRUKTOR
SheduleTableWidget::~SheduleTableWidget()
{
//    delete pFileSystemWatcher;
//    delete pTableWidgetLeft;
////    if(pTableWidgetItem != 0)
////        delete pTableWidgetItem;
//    delete pLayout;
//    delete [] pArrClassLiter;
//    delete [] pArrLessonTime;
////    delete [] tableShedule;
}
