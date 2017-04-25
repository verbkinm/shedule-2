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

    QTableWidget *pTableWidget;     //основная таблица с расписанием
    QTableWidget *pTableWidgetLeft; //таблица с номерами уроков и временем
//    QTableWidget *pTableLeftHeader;
    QTableWidget *pTableRightHeader;//таблица с цифрой и буквой класса

    SheduleDateSwitch           *pSheduleDateSwitch;

    QScrollBar   *pScrollHorizontal, *pScrollVertical;

    QTableWidgetItem *pTableWidgetItem;

    QGridLayout *pLayout;
    MyTouchScreen *pMyTouchScreen;

    QFileSystemWatcher *pFileSystemWatcher;
    bool file_is_exist_today; //local/расписание уроков/на сегодня/сегодня.xml
    bool file_is_exist_yesterday; //local/расписание уроков/на завтра/на завтра.xml

    QList<QTableWidgetItem*> itemsList;

    typedef struct{
        bool visible;
        bool left;
        bool right;
        bool top;
        bool bottom;
    } cell;

    void set_cell(cell *myCell, bool visible, bool left, bool top, bool right, bool bottom);

    cell isCellInSight(QTableWidget* table, QTableWidgetItem* item);

    void convert_html_and_creat_xml();
    void structuring(QDomDocument *pDomDoc);
    void createLeftTable();
    void createRightTable();
    void createSheduleDateSwitch();

    bool stringInList(QStringList, QString);

    bool event(QEvent *event);
    void paintEvent(QPaintEvent * );

public:

    QString currentFile;

    SheduleTableWidget(QWidget *parent = 0);
    ~SheduleTableWidget();

    void setMaximumHeightTableWidget(int);
    void setMaximumHeightTableWidgetLeft(int);

    void setFilter(const QString *filterLesson, const QString *filterTeacher);

signals:
    void signalSetDateSheduleDateSwitch(QString);
//void signalHeaderTextChanged(QString);

public slots:
    void slotChangedFile(const QString & flName); //при смене файла izmenenie.html в папке "на сегодня" пересоздается таблица
                                                  //а при ищменение в папке "на завтра"  ...
    void slotChangedDir (const QString & dirName);

    void slotRecreateTables(QString fileName);

    void slotSetDate(QString);

    void slotMyScreenValueChanchedX(int);
    void slotMyScreenValueChanchedY(int);

    void slotTest();

};

#endif // SheduleTableWidget_H
