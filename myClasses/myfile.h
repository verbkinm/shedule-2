#ifndef MYFILE_H
#define MYFILE_H

#include <QMessageBox>
#include <QFileInfo>
#include <QDate>
#include <QTime>

namespace MySpace {
    bool fileVerification(QFile *file, QString *filePath, bool showMessage = false);

    bool inTheTimeInterval(const QTime &beginInterval, const QTime &endInterval, const QTime &value);

    QDate checkDate(QDate date, char operations = '=');

}

#endif // MYFILE_H
