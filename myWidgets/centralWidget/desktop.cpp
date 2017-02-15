#include "desktop.h"

#include <QStyleOption>
#include <QPainter>
#include <QLabel>
//#include <QDebug>

static int resized = 0;

Desktop::Desktop(QWidget *parent) : QWidget(parent)
{
    pLayout = new QGridLayout;
    pLayout->setContentsMargins(MARGIN_DESKTOP,MARGIN_DESKTOP,MARGIN_DESKTOP,MARGIN_DESKTOP);

    images[0] = ":/img/label-shedule";
    images[1] = ":/img/label-news";
    images[2] = ":/img/label-foto";

    labelText[0] = "РАСПИСАНИЕ УРОКОВ";
    labelText[1] = "НОВОСТИ И ОБЪЯВЛЕНИЯ";
    labelText[2] = "ФОТОАЛЬБОМ";

    this->setLayout(pLayout);
}
void Desktop::setUnits()
{
    for(int i = 0; i < LABEL_COUNTS; i++)
        pLabelShedule[i] = new LabelWorkSpace(labelText[i], images[i]);

    for(int i = 0, label = 0; i < LABEL_COUNTS_ROWS; i++)
        for(int j = 0; j < LABEL_COUNTS / LABEL_COUNTS_ROWS; j++, label++)
            pLayout->addWidget(pLabelShedule[label],i,j);

    for (int var = 0; var < LABEL_COUNTS; ++var) {
        pLabelShedule[var]->applySize(this->size() );
//        qDebug() << "size " << this->size();
    }

    for (int var = 3; var < LABEL_COUNTS; ++var) {
        pLabelShedule[var]->setDisabled(true);
    }

    connect(pLabelShedule[0], SIGNAL(signalClick()), SIGNAL(signalLabel_0_Click()) );
//    qDebug() << " setUnits";
}

bool Desktop::event(QEvent *event)
{
//    qDebug() << event << this->size();
    if(this->isVisible() && event->type() == QEvent::Resize && resized < 1){
//        qDebug() << " center->size " << this->size();
        setUnits();
        resized = 1;
    }



    return QWidget::event(event);
}

void Desktop::paintEvent(QPaintEvent * )
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
Desktop::~Desktop()
{

}
