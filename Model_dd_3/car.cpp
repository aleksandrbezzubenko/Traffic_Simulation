#include "car.h"
#include "tr_light.h"
#include "ui_car.h"
#include <QtWidgets>
#include <QRect>
#include <QPainter>

Car::Car(Tr_Light *_tr_l, int _turn)
    : speed(0), angle(tr_l->angle), tr_l(_tr_l), color(qrand() % 256, qrand() % 256, qrand() % 256)
{
    if(_turn <= 5){
        turn = false;
    } else {
        turn = true;
    }
    if ((_turn % 2) == 0){
        turn_right = false;
    } else {
        turn_right = true;
    }
    setRotation(angle);
}

void Car::advance(int step)
{
    if (!step)
        return;

    const QList<QGraphicsItem *> dangerMice = scene()->items(QPolygonF()
                               << mapToScene(0, 0)
                               << mapToScene(-30, -50)
                               << mapToScene(30, -50));
    speed = 2 + sin(50)*2;
       for (const QGraphicsItem *item : dangerMice) {
           if (item == this)
               continue;
           if (tr_l->crash == false){
               speed = 0;
           }
       }
       if (scene()->collidingItems(this).isEmpty()){
           tr_l->pzdc = true;
           update();
       }
       if (angle == 0){
           if (turn == true){
               if ((turn_right == true) && (this->pos().y() >= 20) && (this->pos().y() <= 30)){
                   setRotation(rotation() + 90);
                   angle += 90;
                   turn = false;
               }
               if ((turn_right == false) && (this->pos().y() >= -40) && (this->pos().y() <= -30)){
                   setRotation(rotation() - 90);
                   angle = 270;
                   turn = false;
               }
           }
           if ((this->pos().y() > 140) && (this->pos().y() < 150) && ((tr_l->color == false) || ((tr_l->yellow >= 3) && (tr_l->yellow <= 4))))
           {
               setPos(mapToParent(0, 0));
           } else {
               setPos(mapToParent(0, -(speed)));
           }
           if ((this->pos().y() >= -310) && (this->pos().y() <= -300)){
               tr_l->Delete_Car();
               delete this;
           }
       }
       if (angle == 90)
       {
           if (turn == true){
               if ((turn_right == true) && (this->pos().x() >= -35) && (this->pos().x() <= -25))
               {
                   setRotation(rotation() + 90);
                   angle += 90;
                   turn = false;
               }
               if ((turn_right == false) && (this->pos().x() >= 25) && (this->pos().x() <= 35))
               {
                   setRotation(rotation() - 90);
                   angle -= 90;
                   turn = false;
               }
           }
           if ((this->pos().x() > -160) && (this->pos().x() < -150) && ((tr_l->color == false) || ((tr_l->yellow >= 3) && (tr_l->yellow <= 4))))
           {
               setPos(mapToParent(0, 0));
           } else {
               setPos(mapToParent(0, -(speed)));
           }
           if ((this->pos().x() >= 450) && (this->pos().x() <= 440)){
               tr_l->Delete_Car();
               delete this;
           }
       }
       if(angle == 180){
           if (turn == true){
               if ((turn_right == true) && (this->pos().y() >= -30) && (this->pos().y() <= -20))
               {
                   setRotation(rotation() + 90);
                   angle += 90;
                   turn = false;
               }
               if ((turn_right == false) && (this->pos().y() >= 30) && (this->pos().y() <= 40))
               {
                   setRotation(rotation() - 90);
                   angle -= 90;
                   turn = false;
               }
           }
           if ((this->pos().y() > -170) && (this->pos().y() < -160) && ((tr_l->color == false) || ((tr_l->yellow >= 3) && (tr_l->yellow <= 4))))
           {
               setPos(mapToParent(0, 0));
           } else {
               setPos(mapToParent(0, -(speed)));
           }
           if ((this->pos().y() >= 310) && (this->pos().y() <= 300)){
               tr_l->Delete_Car();
               delete this;
           }
       }
       if (angle == 270)
       {
           if (turn == true){
               if ((turn_right == true) && (this->pos().x() >= 15) && (this->pos().x() <= 25))
               {
                   setRotation(rotation() + 90);
                   angle = 0;
                   turn = false;
               }
               if ((turn_right == false) && (this->pos().x() >= -45) && (this->pos().x() <= -35))
               {
                   setRotation(rotation() - 90);
                   angle -= 90;
                   turn = false;
               }
           }
           if ((this->pos().x() > 150) && (this->pos().x() < 160) && ((tr_l->color == false) || ((tr_l->yellow >= 3) && (tr_l->yellow <= 4))))
           {
               setPos(mapToParent(0, 0));
           } else {
               setPos(mapToParent(0, -(speed)));
           }
           if ((this->pos().x() >= -450) && (this->pos().x() <= -440)){
               tr_l->Delete_Car();
               delete this;
           }
       }

}

QRectF Car::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-10 - adjust, -20 - adjust,
                      40 + adjust, 40 + adjust);
}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(color);
    painter->drawRect(-10, -20, 20, 40);
    //painter->drawPixmap(0,0, QPixmap("/home/hp/Model_dd_3/images/car_black.svg"));
}


