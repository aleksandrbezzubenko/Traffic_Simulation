#ifndef HIGHT_CAR_H
#define HIGHT_CAR_H

#include "car.h"


class Hight_Car : public Car
{
public:
    Hight_Car(Tr_Light *trl, int _turn, bool _circular_motion, QGraphicsScene *_scene);
    Hight_Car(int angle_car, int _turn, bool _circular_motion, QGraphicsScene *_scene);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
};

#endif // HIGHT_CAR_H
