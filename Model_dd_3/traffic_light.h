#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <QWidget>
#include <QRect>
#include <QPainter>

class Traffic_Light : public QWidget
{
private:
    bool color;
    QPainter painter;
    QRect rect;
public:
    Traffic_Light();
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *);
};

#endif // TRAFFIC_LIGHT_H
