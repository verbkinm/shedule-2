#ifndef SHEDULERIGHTTABLEWIDGET_H
#define SHEDULERIGHTTABLEWIDGET_H

#include "cell.h"

#include <QWidget>
#include <QDomDocument>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QGridLayout>
#include <QFileSystemWatcher>
#include <QFile>

// description of class
    // виджет на вкладки "изменение в расписании"
class SheduleRightTableWidget : public QWidget
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
    QTableWidgetItem *pTableWidgetItem;

    QGridLayout *pLayout;

    QFileSystemWatcher *pFileSystemWatcher;
    bool file_is_exist_today; //local/расписание уроков/на сегодня/сегодня.xml
    bool file_is_exist_yesterday; //local/расписание уроков/на завтра/на завтра.xml


    void convert_html_and_creat_xml();
    void structuring(QDomDocument *pDomDoc);
    void createLeftTable();
    void createRightTable();

    bool fileVerification(QFile *file);


    bool event(QEvent *event);
    void paintEvent(QPaintEvent * );

public:


    QString currentFile;

    QDomDocument *pDomDoc;

    SheduleRightTableWidget(QWidget *parent = 0);
    ~SheduleRightTableWidget();

    QScrollBar *getHorizontalScroolBar();

    void setMaximumHeightTableWidget(int);
    void setMaximumHeightTableWidgetLeft(int);

signals:
    void signalSetDateSheduleDateSwitch(QString);
//    void signalSetTableSize();

public slots:
    void slotChangedFile(const QString & flName); //при смене файла izmenenie.html в папке "на сегодня" пересоздается таблица
    void slotChangedDir (const QString & dirName);

};

#endif // SHEDULERIGHTTABLEWIDGET_H
