#include "footer.h"
#include "generalsettings.h"

#include <QDebug>
#include <QStyleOption>
#include <QPainter>
#include <QApplication>

#define RATIO 80

Footer::Footer(QWidget *parent) : QWidget(parent)//, calendarView(false)
{
    length = sizeof(buttons)/sizeof(buttons[0]);

    buttons[0] = new PushButton(":/img/news", ":/img/news_push");
    buttons[1] = new PushButton(":/img/shedule", ":/img/shedule_push");
    buttons[2] = new PushButton(":/img/home", ":/img/home_push");
    buttons[3] = new PushButton(":/img/help", ":/img/help_push");

    pLayout = new QHBoxLayout;

    panelDateAndTime = new PanelDateAndTime;

    this->setLayout(pLayout);

    connect(buttons[2], SIGNAL(signalClick()),  SLOT(slotStyleApply()) ); // временно
    connect(buttons[2], SIGNAL(signalClick()),  SIGNAL(signalPushHome()) );
    connect(buttons[1], SIGNAL(signalClick()),  SIGNAL(signalPushShedule()) );
    connect(panelDateAndTime, SIGNAL(signalClick()), SIGNAL(signalPushDateAndTime()) );
}
void Footer::disableButtonCurrentWidget(QObject *activeWidget)
{
    int size = sizeof(buttons) / sizeof(buttons[0]);

    for (int i = 0; i < size; ++i)
        buttons[i]->setEnabled(true);

    if(activeWidget->objectName() == OBJECT_NAME_DESKTOP)
        buttons[2]->setEnabled(false);
    if(activeWidget->objectName() == OBJECT_NAME_SHEDULE)
        buttons[1]->setEnabled(false);
}

void Footer::applySize()
{
    currentSize = float(this->height()) / 100 * RATIO;

    pLayout->addWidget(buttons[0]);
    pLayout->addStretch(1);
    pLayout->addWidget(buttons[1]);
    pLayout->addStretch(10);
    pLayout->addWidget(buttons[2]);
    pLayout->addStretch(10);
    pLayout->addWidget(panelDateAndTime);
    pLayout->addStretch(1);
    pLayout->addWidget(buttons[3]);

    for(int i = 0 ; i < length; i++)
        buttons[i]->setSize(QSize(currentSize, currentSize));

    panelDateAndTime->setFixedSize(currentSize*2, currentSize / 100 * 80);
    panelDateAndTime->setFontSize(12);
}
void Footer::paintEvent(QPaintEvent * )
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void Footer::slotStyleApply()
{
    QFile file("/home/verbkinm/myProg/shedule-2/style.qss");
    file.open(QFile::ReadOnly);
    QString strCSS = QLatin1String(file.readAll());
    file.close();
    qApp->setStyleSheet(strCSS);
}

Footer::~Footer()
{
    delete panelDateAndTime;
}
