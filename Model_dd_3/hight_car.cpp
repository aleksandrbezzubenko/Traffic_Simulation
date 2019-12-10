#include "hight_car.h"

Hight_Car::Hight_Car(Tr_Light *trl, int _turn, bool _circular_motion, QGraphicsScene *_scene) : Car(trl, _turn, _circular_motion, _scene)
{}

Hight_Car::Hight_Car(int angle_car, int _turn, bool _circular_motion, QGraphicsScene *_scene) : Car(angle_car, _turn, _circular_motion, _scene)
{}

QRectF Hight_Car::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-10 - adjust, -20 - adjust,
                      30 + adjust, 60 + adjust);
}

void Hight_Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(color);
    //painter->drawRect(-10, -20, 30, 70);
    painter->drawRect(-10, -20, 30, 60);
}
