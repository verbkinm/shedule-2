#include "widget.h"
//#include "myWidgets/centralWidget/shedule/shedule.h"
#include <QApplication>
#include <QFile>
#include "myWidgets/centralWidget/shedule/shedule.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString strCSS = QLatin1String(file.readAll());
    file.close();
    a.setStyleSheet(strCSS);

//    Shedule w;
//    Widget w;
    Shedule w;
//    w.showFullScreen();
    w.showMaximized();

    return a.exec();
}
