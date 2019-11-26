#ifndef TR_LIGHT_H
#define TR_LIGHT_H

#include <QPaintEvent>
#include <QPoint>
#include <QRect>
#include <QTimer>
#include <QPainter>
#include <QLineEdit>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QColor>
#include <cmath>
#include <chrono>
#include <cstdlib>
#include <thread>
#include <vector>
#include "car.h"

class Tr_Light : public QWidget
{
public:
    bool color;
    bool crash;
    bool pzdc;
    int angle;
    int yellow;
    Tr_Light(bool light, int _angle, bool _pzdc);
    QPainter painter;
    QRect rect;
    QTimer *timer;
    QTimer *timer_yellow;
    QVector<Car*> cars;
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *);
    void Push_Car(Car *car);
    void Delete_Car();
public slots:
    void Yellow()
    {
        ++yellow;
        update();
    }
    void ChangeColor()
    {
        color = !color;
        yellow = 0;
        update();
    }
};
#endif // TR_LIGHT_H
