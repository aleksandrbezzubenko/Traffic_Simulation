#include "light_car.h"

Light_Car::Light_Car(Tr_Light *trl, int _turn, bool _circular_motion, QGraphicsScene *_scene) : Car(trl, _turn, _circular_motion, _scene)
{}

Light_Car::Light_Car(int angle_car, int _turn, bool _circular_motion, QGraphicsScene *_scene) : Car(angle_car, _turn, _circular_motion, _scene)
{}

QRectF Light_Car::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-10 - adjust, -20 - adjust,
                      20 + adjust, 40 + adjust);
}

void Light_Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(color);
    painter->drawRect(-10, -20, 20, 40);
}
