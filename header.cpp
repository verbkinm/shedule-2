#include "header.h"

//#include <QDebug>
#include <QStyleOption>
#include <QPainter>

#define RATIO 80

Header::Header(QWidget *parent) : QWidget(parent)
{
    pOwlLabel = new QLabel;
    pLyceumText = new QLabel;

    pLayout = new QHBoxLayout;
    pLayout->addStretch(2);
    pLayout->addWidget(pOwlLabel);
    pLayout->addStretch(20);
    pLayout->addWidget(pLyceumText);
    pLayout->addStretch(2);

    this->setLayout(pLayout);
}
void Header::applySize()
{
    currentSize = float(this->height()) / 100 * RATIO;
    pOwlLabel->setFixedSize(QSize(currentSize, currentSize) );

    QPixmap* buff = new QPixmap(":/img/owl");
    QPixmap* pixOwl = new QPixmap(buff->scaled(currentSize, currentSize, Qt::KeepAspectRatio,Qt::SmoothTransformation) );
    delete buff;
    pOwlLabel->setPixmap(*pixOwl);
    delete pixOwl;

    buff = new QPixmap(":/img/lyceum");
//    qDebug() << currentSize;
    QPixmap* pixLyceum = new QPixmap(buff->scaled(currentSize * 8, currentSize / 100 * 150, Qt::IgnoreAspectRatio) );
    delete buff;
    pLyceumText->setPixmap(*pixLyceum);
    delete pixLyceum;
}
/*virtual*/void Header::paintEvent(QPaintEvent * )
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
Header::~Header()
{

}
