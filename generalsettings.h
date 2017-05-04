#ifndef GENERALSETTINGS
#define GENERALSETTINGS

#if defined (Q_OS_WIN)
    #define PATH_SPLITER "\\"
#elif  defined (Q_OS_LINUX)
    #define PATH_SPLITER "/"
#elif  defined (Q_OS_FREEBSD)
    #define PATH_SPLITER "/"
#endif

//widget
#define SIZE_HEADER 50
#define SIZE_FOOTER 50
//labelworkspace
#define LABEL_COUNTS 9
#define LABEL_COUNTS_ROWS 2

//calendar
#define OBJECT_NAME_CALENDAR "Calendar"
//desktop
#define OBJECT_NAME_DESKTOP "Desktop"
//shedule
#define OBJECT_NAME_SHEDULE "Shedule"

//
#define MARGIN_DESKTOP 50
//labelworkspace
#define FONT_SIZE_LABEL_WORK_SPACE 14 //24
#define FONT_PUSH_SIZE FONT_SIZE_LABEL_WORK_SPACE - 1

//sheduleleftpanel
#define FONT_SHEDULE_LEFT_PANEL_TREE_ROOT 20
#define FONT_SHEDULE_LEFT_PANEL_TREE_TRAVERS_NODE 10
#define TEXT_VERTICAL_LABEL_LESSONS "ПРЕДМЕТЫ"

//sheduletable
#define FONT_SHEDULE_RIGHT_HEADER 20
#define STRING_LENGHT_SHEDULE_RIGHT_HEADER 70
#define HEADER_SIZE_HEIGHT 80
//#define SHEDULE_DATE_SIZE_WIDTH 200

//sheduletable
#define FONT_SIZE_TABLE_SHEDULE 12
#define SCROLL_BAR_WIDTH 20

//sheduletablewidget
#define SHARE_FILE_MAIN_SHEDULE_TODAY QString("share"+QString(PATH_SPLITER)+"расписание уроков"+QString(PATH_SPLITER)+"на сегодня"+QString(PATH_SPLITER)+"izmenenie.html")
#define SHARE_DIR_MAIN_SHEDULE_TODAY QString("share"+QString(PATH_SPLITER)+"расписание уроков"+QString(PATH_SPLITER)+"на сегодня")
#define SHARE_FILE_MAIN_SHEDULE_YESTERDAY QString("share"+QString(PATH_SPLITER)+"расписание уроков"+QString(PATH_SPLITER)+"на завтра"+QString(PATH_SPLITER)+"izmenenie.html")
#define SHARE_DIR_MAIN_SHEDULE_YESTERDAY QString("share"+QString(PATH_SPLITER)+"расписание уроков"+QString(PATH_SPLITER)+"на завтра")
#define SHARE_ARCHIVE_PATH QString("share"+QString(PATH_SPLITER)+"расписание уроков"+QString(PATH_SPLITER)+"архив")
#define NOT_EVEN_ROW_COLOR QColor(219,219,219) // цвет нечетной строки в таблице
#define DEFAULT_BACKGROUND_COLOR QColor(Qt::white)
#define FILTRED_CELL QColor(226,102,31)
#define BACKGROUND_COLOR_CURRENT_LESSON QColor(Qt::green)

#define LOCAL_FILE_MAIN_SHEDULE_TODAY QString("local"+QString(PATH_SPLITER)+"расписание уроков"+QString(PATH_SPLITER)+"на сегодня"+QString(PATH_SPLITER)+"сегодня.xml")
#define LOCAL_FILE_MAIN_SHEDULE_YESTERDAY QString("local"+QString(PATH_SPLITER)+"расписание уроков"+QString(PATH_SPLITER)+"на завтра"+QString(PATH_SPLITER)+"на завтра.xml")
#define LOCAL_ARCHIVE_PATH QString("local"+QString(PATH_SPLITER)+"расписание уроков"+QString(PATH_SPLITER)+"архив")

//sheduledateswitch
#define SHEDULE_DATE_SWITCH_BUTTON_SIZE 70
#define SHEDULE_DATE_TEXT_SIZE 32

//#define SHEDULE_DATE_QLINEEDIT_WIDTH 300
#define SHEDULE_DATE_ARCHIVE_LIMIT_MIN "2010"
#define SHEDULE_DATE_ARCHIVE_LIMIT_MAX "2020"
//
#define TEXT_ROOT_LIST "Предметы:"
#define TEXT_SHEDULE_DEFAULT "Расписание:"

//shedule
#define LEFT_PANEL_TREE_WIDTH 200

//verticallabel
#define VERTICAL_LABEL_WIDTH 50
//


#endif // GENERALSETTINGS

