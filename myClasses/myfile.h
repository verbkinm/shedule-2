#ifndef MYFILE_H
#define MYFILE_H

#include <QMessageBox>
#include <QFileInfo>


bool fileVerification(QFile *file, QString *filePath)
{
    if(!file->isOpen() && !file->open(QIODevice::ReadOnly) ){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(QString("Невозможно открыть файл: \"" + QFileInfo(*file).absoluteFilePath() ) + \
                       "\" для чтения");
        msgBox.exec();
        return false;
    }
    *filePath = QFileInfo(*file).absoluteFilePath();
    return true;
}

#endif // MYFILE_H
