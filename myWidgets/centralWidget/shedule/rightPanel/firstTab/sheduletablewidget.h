#ifndef SheduleTableWidget_H
#define SheduleTableWidget_H

#include "cell.h"
#include "sheduledateswitch.h"
#include "myClasses/mytouchscreen.h"

#include <QWidget>
#include <QDomDocument>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QGridLayout>
#include <QFileSystemWatcher>
#include <QFile>

// description of class
    // виджет на вкладки "изменение в расписании"
class SheduleTableWidget : public QWidget
{
    Q_OBJECT
private:
    QDomNode root;

    int numberOfLesson;
    int numberOfCollum;
    int numberOfRow;
    int numberOfClass;

    QString *pArrClassLiter; //number and literal
    QString *pArrLessonTime;
//    QString *allTextInFile;
    Cell **tableShedule;

    QTableWidget *pTableWidget;
    QTableWidget *pTableWidgetLeft;
    QTableWidget *pTableLeftHeader;
    QTableWidget *pTableRightHeader;

    SheduleDateSwitch           *pSheduleDateSwitch;

    QScrollBar   *pScrollHorizontal, *pScrollVertical;

    QTableWidgetItem *pTableWidgetItem;

    QGridLayout *pLayout;
    MyTouchScreen *pMyTouchScreen;

    QFileSystemWatcher *pFileSystemWatcher;
    bool file_is_exist_today; //local/расписание уроков/на сегодня/сегодня.xml
    bool file_is_exist_yesterday; //local/расписание уроков/на завтра/на завтра.xml


    void convert_html_and_creat_xml();
    void structuring(QDomDocument *pDomDoc);
    void createLeftTable();
    void createRightTable();
    void createSheduleDateSwitch();

    bool event(QEvent *event);
    void paintEvent(QPaintEvent * );

public:

    QString currentFile;

    SheduleTableWidget(QWidget *parent = 0);
    ~SheduleTableWidget();

//    QScrollBar *getHorizontalScroolBar();
//    QScrollBar *getVerticalScroolBar();

    void setMaximumHeightTableWidget(int);
    void setMaximumHeightTableWidgetLeft(int);

//    void addWidget(QWidget*widget);

signals:
    void signalSetDateSheduleDateSwitch(QString);
//    void signalSetTableSize();

public slots:
    void slotChangedFile(const QString & flName); //при смене файла izmenenie.html в папке "на сегодня" пересоздается таблица
    void slotChangedDir (const QString & dirName);

    void slotRecreateTables(QString fileName);

    void slotSetDate(QString);

    void slotMyScreenValueChanchedX(int);
    void slotMyScreenValueChanchedY(int);

    void slotTest(int,int);

};

#endif // SheduleTableWidget_H
