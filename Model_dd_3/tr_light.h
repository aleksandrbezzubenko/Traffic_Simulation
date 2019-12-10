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
    QVector<Car*> cars;
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *);
    void Push_Car(Car *car);
    void Delete_Car();
    static void Create_Car(Tr_Light *trl, QGraphicsScene *scene, int _limite_type_car);
    static void timer_start(unsigned int interval, Tr_Light *trl, QGraphicsScene *scene, int _limite_type_car);
public slots:
    void Change_Timer_Create_Car(int time)
    {
        _interval = 1000*time;
    }
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
