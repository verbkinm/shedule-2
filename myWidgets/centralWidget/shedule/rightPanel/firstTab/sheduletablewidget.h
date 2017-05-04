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
#include <QTimer>
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
    QString *pArrLessonTime; // время начала и конца урока

    QString lessonFilter, teacherFilter;
    Cell **tableShedule;    //массив для хранения данных ячеек

    QTableWidget *pTableWidget;     //основная таблица с расписанием
    QTableWidget *pTableWidgetLeft; //таблица с номерами уроков и временем
    QTableWidget *pTableRightHeader;//таблица с цифрой и буквой класса

    QTimer timerForslotSetBackgroundCurrentLesson;

    SheduleDateSwitch           *pSheduleDateSwitch; // панель отображения и переключения даты расписания

    QScrollBar   *pScrollHorizontal, *pScrollVertical; // скроллбары для основной таблицы

    QTableWidgetItem *pTableWidgetItem;

    QGridLayout *pLayout;
    MyTouchScreen *pMyTouchScreen;  // класс "тачскрина" для листания таблицы одним пальцем

    QLabel *arrArrow[8]; // стрелки на основной таблице

    QFileSystemWatcher *pFileSystemWatcher;
    bool file_is_exist_today; //local/расписание уроков/на сегодня/сегодня.xml
    bool file_is_exist_yesterday; //local/расписание уроков/на завтра/на завтра.xml

    QList<QTableWidgetItem*> itemsList;  // список ячеек(QTableWidgetItem*) попавших под фильтр

    typedef struct{
        bool visibleX;
        bool visibleY;
        bool left;
        bool right;
        bool top;
        bool bottom;
    } cell; // структура обнаружения, где ячейка? В поле видимости  слева, или справа и т.д.

    void set_cell(cell *myCell, bool visibleX, bool visibleY, bool left, bool top, bool right, bool bottom); // установка параметров структуры cell

    cell isCellInSight(QTableWidget* table, QTableWidgetItem* item); // ячейка в поле видимости?

    void convert_html_and_creat_xml();
    void structuring(QDomDocument *pDomDoc);    // создание QDomDocument из файла xml
    void createLeftTable();                     // создание таблицы с номерами уроков и временем
    void createRightTable();                    // создание таблицы основной
    void creatArrowsForTable();                 // создание стрелок направления для pTableWidget
    void createSheduleDateSwitch();             // создание панели переключения дней

    bool isStringInList(QStringList, QString);  // проверка вхождения строки в список строк

    bool event(QEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
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
    void signalChangeCurrentLesson(int lesson);

private slots:
    void slotChangedFile(const QString & flName); //при смене файла izmenenie.html в папке "на сегодня" пересоздается таблица
                                                  //а при изменение в папке "на завтра"  ...
    void slotChangedDir (const QString & dirName);

    void slotRecreateTables(QString fileName);

    void slotSetDate(QString);

    void slotMyScreenValueChanchedX(int);
    void slotMyScreenValueChanchedY(int);

    void slotArrowsVisible(); // включение и отключение видимости arrArrow[i]

    void slotSetBackgroundCurrentLesson(); // выделение цветом текущего урока
    void slotChangeCurrentLesson(int lesson); // перекрашивание ячеек в цвет != цвету текущего урока
};

#endif // SheduleTableWidget_H
