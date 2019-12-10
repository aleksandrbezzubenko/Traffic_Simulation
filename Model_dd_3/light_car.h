#ifndef LIGHT_CAR_H
#define LIGHT_CAR_H

#include "car.h"


class Light_Car : public Car
{
public:
    Light_Car(Tr_Light *trl, int _turn, bool _circular_motion, QGraphicsScene *_scene);
    Light_Car(int angle_car, int _turn, bool _circular_motion, QGraphicsScene *_scene);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
};

#endif // LIGHT_CAR_H
