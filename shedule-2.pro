    #-------------------------------------------------
#
# Project created by QtCreator 2016-10-13T23:37:31
#
#-------------------------------------------------

QT       += core gui

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
    myWidgets/centralWidget/shedule/sheduleright.cpp

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
    myWidgets/centralWidget/shedule/sheduleright.h

#INCLUDEPATH += ./

RESOURCES += \
    src.qrc
