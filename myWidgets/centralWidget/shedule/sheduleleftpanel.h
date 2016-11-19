#ifndef SHEDULELEFTPANEL_H
#define SHEDULELEFTPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>

class SheduleLeftPanel : public QWidget
{
    Q_OBJECT
public:
    SheduleLeftPanel(QWidget *parent = 0);

    QListWidget* pListWidget;

    void setUnits();

private:
    QWidget* pParent;
    QVBoxLayout* pLayout;


    bool event(QEvent *event);
    void paintEvent(QPaintEvent * );

signals:

public slots:
};

#endif // SHEDULELEFTPANEL_H
