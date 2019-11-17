#ifndef CAR_H
#define CAR_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QPainter>
#include <ui_car.h>
//#include "zagolovok.h"
//#include <tr_light.h>

class Tr_Light;

class Car : public QGraphicsItem
{
public:
    Car(bool light, bool _x, bool _turn, bool _turn_right, int _angle);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void Change_Light();

protected:
    void advance(int step) override;
public slots:
    void Create_Car(Tr_Light *trl, QGraphicsScene *scene);
private:
    bool turn;
    bool turn_right;
    bool x;
    bool trl;
    int angle;
    qreal speed;
    QColor color;
};

#endif // CAR_H
