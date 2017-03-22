#include "widget.h"
//#include "myWidgets/centralWidget/shedule/shedule.h"
//#include "myWidgets/centralWidget/shedule/sheduledateswitch.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString strCSS = QLatin1String(file.readAll());
    file.close();
    a.setStyleSheet(strCSS);

//    Shedule w;
    Widget w;
//    SheduleDateSwitch w;

//    w.showFullScreen();
    w.showMaximized();
//    w.show();

    return a.exec();
}
