#ifndef VERTICALLABEL_H
#define VERTICALLABEL_H

#include <QLabel>
#include <QPushButton>

class VerticalLabel : public QLabel
{
    Q_OBJECT
public:
    QString text;

    VerticalLabel(QString text = 0);
    ~VerticalLabel();

private:
    void mouseReleaseEvent(QMouseEvent*);

    void paintEvent(QPaintEvent *);

signals:
    void signalClicked();
};

#endif // VERTICALLABEL_H
