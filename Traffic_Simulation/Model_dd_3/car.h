#ifndef CAR_H
#define CAR_H

#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <ui_car.h>

class Car : public QGraphicsItem
{
public:
    Car();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

protected:
    void advance(int step) override;

private:
    qreal angle;
    qreal speed;
    //qreal mouseEyeDirection;
    QColor color;
};

#endif // CAR_H
