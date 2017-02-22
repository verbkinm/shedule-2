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
#define SIZE_IN_PERCENT_HEADER 15
#define SIZE_IN_PERCENT_FOOTER 15

//labelworkspace
#define LABEL_COUNTS 8
#define LABEL_COUNTS_ROWS 2

#define MARGIN_DESKTOP 50

#define FONT_SIZE 14 //24
#define FONT_PUSH_SIZE FONT_SIZE - 1

//sheduleleftpanel
#define FONT_SHEDULE_LEFT_PANEL_TREE_ROOT 20
#define FONT_SHEDULE_LEFT_PANEL_TREE_TRAVERS_NODE 10

//sheduleright
#define FONT_SHEDULE_RIGHT_HEADER 20
#define STRING_LENGHT_SHEDULE_RIGHT_HEADER 70
//
#define TEXT_ROOT_LIST "Предметы:"
#define TEXT_SHEDULE_DEFAULT "Расписание:"

#endif // GENERALSETTINGS

