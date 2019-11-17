#include "car.h"
#include "tr_light.h"
#include "ui_car.h"

#include <QtWidgets>
#include <QRect>
#include <QPainter>

Car::Car(bool light, bool _x, bool _turn, bool _turn_right, int _angle)
    : speed(0), trl(light), x(_x), angle(_angle), turn(_turn), turn_right(_turn_right), color(qrand() % 256, qrand() % 256, qrand() % 256)
{
    setRotation(angle);
}

void Car::Create_Car(Tr_Light *trl, QGraphicsScene *scene)
{
    /*Car *car = new Car();
    //car->setPos(::sin((i * 6.28) / CarCount) * 200,
      //            ::cos((i * 6.28) / CarCount) * 200);
    car->setPos(100, 150);
    trl.Push_Car(car);
    //if (car->pos.y() == )
    scene->addItem(car);*/
}

void Car::advance(int step)
{
    if (!step)
        return;

    const QList<QGraphicsItem *> dangerMice = scene()->items(QPolygonF()
                               << mapToScene(0, 0)
                               << mapToScene(0, -20)
                               << mapToScene(0, -20));
    speed = 2 + sin(50)*2;
        for (const QGraphicsItem *item : dangerMice) {
            if (item == this)
                continue;
            speed = 0;
        }
       if (x == true)
       {
           if ((turn == true) && (this->pos().x() >= 0) && (this->pos().x() <= 10))
           {
               setRotation(rotation() + 90);
               turn = false;
           }
           if ((this->pos().x() > 150) && (this->pos().x() < 160) && (trl == false))
           {
               setPos(mapToParent(0, 0));
           } else {
               setPos(mapToParent(0, -(speed)));
           }
       } else {
           if ((turn == true) && (this->pos().y() >= 20) && (this->pos().y() <= 30))
           {
               setRotation(rotation() + 90);
               turn = false;
           }
           if ((this->pos().y() > 150) && (this->pos().y() < 160) && (trl == false))
           {
               setPos(mapToParent(0, 0));
           } else {
               setPos(mapToParent(0, -(speed)));
           }
       }
}

QRectF Car::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(color);
    painter->drawRect(-10, -20, 20, 40);
}

void Car::Change_Light()
{
    trl = !trl;
}


