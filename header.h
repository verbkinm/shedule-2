#ifndef HEADER_H
#define HEADER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

class Header : public QWidget
{
    Q_OBJECT
public:
    Header(QWidget *parent = 0);
    ~Header();

    void applySize();

private:
    int length;
    float currentSize;
    QHBoxLayout* pLayout;
    QLabel *pOwlLabel, *pLyceumText;

    void paintEvent(QPaintEvent * );

signals:

public slots:
};

#endif // HEADER_H
