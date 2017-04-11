#ifndef MYFILE_H
#define MYFILE_H

#include <QMessageBox>
#include <QFileInfo>
#include <QDate>

namespace MySpace {
    bool fileVerification(QFile *file, QString *filePath);
    QDate checkDate(QDate date, char operations = '=');
}

#endif // MYFILE_H
