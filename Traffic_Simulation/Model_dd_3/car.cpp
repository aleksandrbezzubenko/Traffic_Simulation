#include "car.h"
#include "ui_car.h"

#include <QtWidgets>
#include <QRect>
#include <QPainter>
#include <QPixmap>

const qreal Pi = M_PI;
const qreal TwoPi = 2 * M_PI;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

Car::Car()
    : angle(0), speed(0), color(qrand() % 256, qrand() % 256, qrand() % 256)
{
    setRotation(270);
}

void Car::advance(int step)
{
    if (!step)
        return;
    QList<QGraphicsItem *> dangerMice = scene()->items(QPolygonF()
                                                          << mapToScene(50, 0)
                                                          << mapToScene(-100, -50)
                                                          << mapToScene(100, -50));
       foreach (QGraphicsItem *item, dangerMice) {
           if (item == this)
               continue;

           QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));
           qreal angleToMouse = ::acos(lineToMouse.dx() / lineToMouse.length());
           if (lineToMouse.dy() < 0)
               angleToMouse = TwoPi - angleToMouse;
           angleToMouse = normalizeAngle((Pi - angleToMouse) + Pi / 2);

           if (angleToMouse >= 0 && angleToMouse < Pi / 2) {
               // Rotate right
               angle += 0.5;
           } else if (angleToMouse <= TwoPi && angleToMouse > (TwoPi - Pi / 2)) {
               // Rotate left
               angle -= 0.5;
           }
       }
       speed += (-50 + qrand() % 100) / 100.0;
       setPos(mapToParent(0, -(3 + sin(speed) * 2)));
       scene()->collidingItems(this).isEmpty() ? speed = speed : speed = 0;
}

QRectF Car::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPixmap picture("\\resourses\\car.jpg");
    painter->setBrush(color);
    painter->drawPixmap(0, 0, picture);
    //painter->drawRect(-10, -20, 20, 40);
}


