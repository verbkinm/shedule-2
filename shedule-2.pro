QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shedule-2
TEMPLATE = app


SOURCES += main.cpp\
    widget.cpp \
    footer.cpp \
    myWidgets/pushbutton.cpp \
    myWidgets/paneldateandtime.cpp \
    header.cpp \
    center.cpp \
    myWidgets/centralWidget/desktop.cpp \
    myWidgets/labelworkspace.cpp \
    myWidgets/centralWidget/calendar.cpp \
    myWidgets/centralWidget/shedule/shedule.cpp \
    myWidgets/centralWidget/shedule/sheduleleftpanel.cpp \
    myWidgets/centralWidget/shedule/rightPanel/sheduleright.cpp \
    myWidgets/centralWidget/shedule/inherited/mytreewidget.cpp \
    myWidgets/centralWidget/shedule/inherited/verticallabel.cpp \
    myWidgets/centralWidget/shedule/rightPanel/firstTab/cell.cpp \
    myWidgets/centralWidget/shedule/rightPanel/firstTab/sheduledateswitch.cpp \
    myWidgets/centralWidget/shedule/inherited/mylineedit.cpp \
    myWidgets/converter_main_table_shedule.cpp \
    myClasses/trackingdate.cpp \
    myClasses/myfile.cpp \
    myWidgets/centralWidget/shedule/inherited/myfilter.cpp \
    myWidgets/centralWidget/shedule/rightPanel/firstTab/sheduletablewidget.cpp \
    myClasses/mytouchscreen.cpp

HEADERS  += widget.h \
    footer.h \
    myWidgets/pushbutton.h \
    myWidgets/paneldateandtime.h \
    header.h \
    center.h \
    myWidgets/centralWidget/desktop.h \
    myWidgets/labelworkspace.h \
    generalsettings.h \
    myWidgets/centralWidget/calendar.h \
    myWidgets/centralWidget/shedule/shedule.h \
    myWidgets/centralWidget/shedule/sheduleleftpanel.h \
    myWidgets/centralWidget/shedule/rightPanel/sheduleright.h \
    myWidgets/centralWidget/shedule/inherited/mytreewidget.h \
myWidgets/centralWidget/shedule/inherited/verticallabel.h \
    myWidgets/centralWidget/shedule/rightPanel/firstTab/cell.h \
    myWidgets/centralWidget/shedule/rightPanel/firstTab/sheduledateswitch.h \
    myWidgets/centralWidget/shedule/inherited/mylineedit.h \
    myWidgets/converter_main_table_shedule.h \
    mythread.h \
    myClasses/mythread.h \
    myClasses/trackingdate.h \
    myClasses/myfile.h \
    myWidgets/centralWidget/shedule/inherited/myfilter.h \
    myWidgets/centralWidget/shedule/rightPanel/firstTab/sheduletablewidget.h \
    myClasses/mytouchscreen.h

#INCLUDEPATH += ./

RESOURCES += src.qrc

FORMS += \
    indevelopment.ui
