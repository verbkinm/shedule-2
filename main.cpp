#include "widget.h"
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

    Widget w;
    w.showFullScreen();
//    w.show();

    return a.exec();
}
