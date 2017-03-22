#ifndef SHEDULERIGHTTABLEWIDGET_H
#define SHEDULERIGHTTABLEWIDGET_H

#include "cell.h"
#include "../../converter_main_table_shedule.h"

#include <QWidget>
#include <QDomDocument>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QGridLayout>
#include <QFileSystemWatcher>

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
    QString *allTextInFile;
    Cell **tableShedule;

    QTableWidget *pTableWidget;
    QTableWidget *pTableWidgetLeft;
    QTableWidgetItem *pTableWidgetItem;

    QGridLayout *pLayout;

    Converter_main_table_shedule *pConverter_main_table_shedule;
    QFileSystemWatcher *pFileSystemWatcher;
    bool file_is_exist;

    void convert_html_and_creat_xml();
    void structuring(QDomDocument *pDomDoc);
    void createLeftTable();
    void createRightTable();

    bool fileVerification(QFile *file);


    void paintEvent(QPaintEvent * );

public:
    QFile currentFile;

    QDomDocument *pDomDoc;

    SheduleRightTableWidget(QWidget *parent = 0);

    QScrollBar *getHorizontalScroolBar();

signals:
    void signalSetDateSheduleDateSwitch();
public slots:
    void slotChangedFile(const QString & flName);
    void slotChangedDir (const QString & dirName);

    void slotTest();
};

#endif // SHEDULERIGHTTABLEWIDGET_H
