#ifndef CONVERTER_MAIN_TABLE_SHEDULE_H
#define CONVERTER_MAIN_TABLE_SHEDULE_H

#include <QObject>
#include <QFileInfo>

//descripton class
    //конвертирет файл share\расисание уроков\на сегодня\izmenenie.html в файл local\расписание уроков\на сегодня\сегодня.xml
    //и копирует файлы в папки архивов share\расисание уроков\архив и local\расисание уроков\архив согластно дате
    //иерархия папки архив: год\месяц\день
class Converter_main_table_shedule : public QObject
{
    Q_OBJECT
public:
    Converter_main_table_shedule(QString read_file, QString write_file, QObject *parent = 0);

private:
    QFile fileXmlOut, fileHtmlIn;

    void clearTag(QString *string, int *positionString, int indexStart, int indexEnd);
    void removeExcess(QString *string);
    void copyFilesInArchive();

signals:

public slots:
};

#endif // CONVERTER_MAIN_TABLE_SHEDULE_H
