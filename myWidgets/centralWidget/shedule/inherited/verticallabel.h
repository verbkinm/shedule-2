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

private:
    void mouseReleaseEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);

    void paintEvent(QPaintEvent *);

signals:
    void pressed();
    void released();
};

#endif // VERTICALLABEL_H
