#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QTextCodec>
#include <QDomDocument>

void clearTag(QString *string, int *positionString, int indexStart, int indexEnd)
{
    int lenghtString = indexEnd - indexStart;
    QString buff = string->mid(indexStart,lenghtString + 1);
    if(buff.indexOf(" ") > 0){
        int indexSpace = buff.indexOf(" ");
        string->remove(indexSpace + indexStart, lenghtString - indexSpace);
        *positionString = indexStart + indexSpace;
    }
}
void removeExcess(QString *string)
{
    string->remove("&nbsp;");
    string->remove("<caption>");string->remove("</caption>");
    string->remove("<h1>");string->remove("</h1>");
    string->remove("<strong>");string->remove("</strong>");
    string->remove("Расписание классов");
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if(argc < 2){
        qDebug() << "error: not specified the file name";
        exit(1);
    }
    QFile *pFile = new QFile(argv[1]);
    if(!pFile->open(QIODevice::ReadOnly) ){
        qDebug() << "Невозможно открыть файл";
        exit(1);
    }

    QByteArray html = pFile->readAll();
    QTextCodec* defaultTextCodec = QTextCodec::codecForName("Windows-1251");
    QString unicode = defaultTextCodec->toUnicode(html);

    int indexStart  = unicode.indexOf("<table");
    QString buff;

    int j = 0;
    for (int i = unicode.size(); i != 0; --i, ++j)
        buff[j] = unicode[i];

    int indexEnd    = buff.indexOf(">elbaT/<");
    QString allFile = unicode.mid( indexStart, unicode.size() - indexStart - indexEnd + 1 ); // from <table to </Table>

    bool inTag          = false;
    bool attachedTag    = false;
    indexStart          = -1;
    indexEnd            = -1;

//Clear tags
    for (int i = 0; i < allFile.size(); ++i) {
        QChar c = allFile[i];
        if(inTag)
            allFile[i] = c.toLower();
        if(allFile[i] == '<'){
            if(inTag){
                attachedTag = true;
                continue;
            }
            inTag = true;
            indexStart = i;
        }
        if(allFile[i] == '>'){
            if(attachedTag){
                attachedTag = false;
                continue;
            }
            inTag = false;
            indexEnd = i;
            clearTag(&allFile , &i, indexStart, indexEnd);
        }
    }

    removeExcess(&allFile);
    QString xmlFormat = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    xmlFormat.append(allFile);

    QDomDocument domDoc;
    domDoc.setContent(allFile);
    QDomElement root = domDoc.documentElement();
    qDebug() << root.nodeName();
    QDomNodeList nodeList = root.childNodes();
    QDomNode firstCell, secondCell; //empty TD tag in first TR, and TD with rowspan(day of week)
    firstCell   = nodeList.at(0).firstChild();
    secondCell  = nodeList.at(1).firstChild();
    nodeList.at(0).removeChild(firstCell);
    nodeList.at(1).removeChild(secondCell);

    for (int i = 0; i < nodeList.size(); ++i) {
        qDebug() << nodeList.at(i).nodeName() << nodeList.at(i).childNodes().size();
    }

    QFile pFileXmlOut(QFileInfo(*pFile).path() + "/out.xml");
    pFileXmlOut.open(QIODevice::WriteOnly | QIODevice::Text);
    pFileXmlOut.write(domDoc.toByteArray());
    pFileXmlOut.close();
    pFile->close();

    exit(0);
    return a.exec();
}

