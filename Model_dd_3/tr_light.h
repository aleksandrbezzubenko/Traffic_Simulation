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
#include "light_car.h"
#include "hight_car.h"

class Tr_Light : public QWidget
{
public:
    bool color;
    bool crash;
    int _interval;
    int angle;
    int yellow;
    Tr_Light(bool light, int _angle, int timer_light);
    QPainter painter;
    QRect rect;
    QTimer *timer;
    QTimer *timer_yellow;
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *);
public slots:
    void Change_Timer_Create_Car(int time);
    void Yellow();
    void ChangeColor();
};
#endif // TR_LIGHT_H
