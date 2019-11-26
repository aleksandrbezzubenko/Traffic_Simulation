#ifndef CAR_H
#define CAR_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QPainter>
#include <random>
#include <ctime>
#include <ui_car.h>
//#include "zagolovok.h"
//#include <tr_light.h>

class Tr_Light;

class Car : public QGraphicsItem
{
public:
    Car(Tr_Light *_tr_l, int _turn);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void Change_Light();
protected:
    void advance(int step) override;
private:
    Tr_Light *tr_l;
    bool turn;
    bool turn_right;
    int angle;
    qreal speed;
    QColor color;
};

#endif // CAR_H
