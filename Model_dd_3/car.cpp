#include "car.h"
#include "tr_light.h"
#include "ui_car.h"
#include <QtWidgets>
#include <QRect>
#include <QPainter>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

Car::Car(Tr_Light *trl, int _turn, bool _circular_motion, QGraphicsScene *_scene)
    : speed(0), tr_l(trl), angle(tr_l->angle), game_over(false), circular_motion(_circular_motion), turn_in(false), scene(_scene),color(qrand() % 256, qrand() % 256, qrand() % 256)
{
    borders_h = 30;
    borders_w = 50;
    if (angle == 0){
        angle_exit_t = 180;
        angle_exit_f = 270;
    }
    if (angle == 90){
        angle_exit_t = 270;
        angle_exit_f = 0;
    }
    if (angle == 180){
        angle_exit_t = 0;
        angle_exit_f = 90;
    }
    if (angle == 270){
        angle_exit_t = 90;
        angle_exit_f = 180;
    }
    if(_turn <= 5){
        turn = false;
    } else {
        turn = true;
    }
    if ((_turn % 2) == 0){
        turn_right = false;
        angle_1 = 90;
    } else {
        turn_right = true;
        angle_1 = 0;
    }
    setRotation(angle);
}

Car::Car(int angle_car, int _turn, bool _circular_motion, QGraphicsScene *_scene)
    : speed(0), angle_in_circular_motoin(0.5), angle(angle_car), game_over(false), circular_motion(_circular_motion), turn_in(false), scene(_scene),color(qrand() % 256, qrand() % 256, qrand() % 256)
{
    if (angle == 0){
        angle_exit_t = 180;
        angle_exit_f = 270;
    }
    if (angle == 90){
        angle_exit_t = 270;
        angle_exit_f = 0;
    }
    if (angle == 180){
        angle_exit_t = 0;
        angle_exit_f = 90;
    }
    if (angle == 270){
        angle_exit_t = 90;
        angle_exit_f = 180;
    }
    if(_turn <= 5){
        turn = false;
    } else {
        turn = true;
    }
    if ((_turn % 2) == 0){
        turn_right = false;
        angle_1 = 90;
    } else {
        turn_right = true;
        angle_1 = 0;
    }
    setRotation(angle);
}

void Car::advance(int step)
{
    if (!step)
        return;
    if (circular_motion){
        if (turn_in){
            borders_h = 20;
            borders_w = 25;
        } else {
            borders_h = 60;
            borders_w = 60;
        }
    }

    const QList<QGraphicsItem *> dangerMice = scene->items(QPolygonF()
                               << mapToScene(0, 0)
                               << mapToScene(-borders_h, -borders_w)
                               << mapToScene(borders_h, -borders_w));
    //speed = 2 + sin(50)*2
    speed = 1.5;
    angle_in_circular_motoin = 0.5;
       for (const QGraphicsItem *car : dangerMice) {
           if (car == this){
               continue;
           } else {
               speed = 0;
               angle_in_circular_motoin = 0;
           }
           if (!circular_motion){
               if ((tr_l->crash == false) || (tr_l->crash && ((this->pos().y() > 100) || (this->pos().y() < -130) ||
                                                          (this->pos().x() < -120) || (this->pos().x() > 110)))){
                   speed = 0;
               }
           }
       }
       if (!scene->collidingItems(this).isEmpty() && (this->pos().y() < 100) &&
               (this->pos().y() > -130) && (this->pos().x() > -120) && (this->pos().x() < 110)){
           if (!game_over && tr_l->crash) {
               timer_go(scene, this);
               game_over = true;
           }
           //QTimer *timer_turn_right = new QTimer;
           //QGraphicsScene::connect(timer_turn_right, SIGNAL(timeout()), scene, SLOT(Car::Turn_right()));
           //timer_turn_right->start(4000);
           tr_l->crash = false;
           speed = 0;
           update();
       }
       if (circular_motion){

           setPos(mapToParent(0, -(speed)));
           if (turn_in == true){
               setRotation(rotation() - angle_in_circular_motoin);
               if (turn == true){
                   if ((rotation() == (angle + 15)) && (turn_right == true)){
                       setRotation(rotation() + 75);
                       //Rotation_Right();
                       turn_in = false;
                       if (angle == 270){
                           angle = 0;
                       } else {
                           angle += 90;
                       }
                   } else if ((rotation() == (angle - 165)) && (turn_right == false)){
                       //Rotation_Right();
                       setRotation(rotation() + 75);
                       turn_in = false;
                       if (angle == 0){
                           angle = 270;
                       } else {
                           angle -= 90;
                       }
                   }
               } else {
                   if (rotation() == (angle - 75)){
                       //Rotation_Right();
                       setRotation(rotation() + 75);
                       turn_in = false;
                   }
               }
           }
           if (angle == 0){
               if ((turn_in == false) && (this->pos().y() >= 160) && (this->pos().y() <= 170)){
                   //Rotation_Right();
                   setRotation(rotation() + 80);
                   turn_in = true;
               }
               if ((this->pos().y() >= -310) && (this->pos().y() <= -300)){
                   delete this;
               }
           }
           if (angle == 90){
               if ((turn_in == false) && (this->pos().x() > -180) && (this->pos().x() < -170)){
                   //Rotation_Right();
                   setRotation(rotation() + 80);
                   turn_in = true;
               }
               if ((this->pos().x() >= 340) && (this->pos().x() <= 350)){
                   delete this;
               }
           }
           if (angle == 180){
               if ((turn_in == false) && (this->pos().y() >= -170) && (this->pos().y() <= -150)){
                   //Rotation_Right();
                   setRotation(rotation() + 80);
                   turn_in = true;
               }
               if ((this->pos().y() >= 300) && (this->pos().y() <= 310)){
                   delete this;
               }
           }
           if (angle == 270){
               if ((turn_in == false) && (this->pos().x() > 160) && (this->pos().x() < 170)){
                   //Rotation_Right();
                   setRotation(rotation() + 80);
                   turn_in = true;
               }
               if ((this->pos().x() >= -350) && (this->pos().x() <= -340)){
                   delete this;
               }
           }
           /*if (turn_in == true){
               setRotation(rotation() - 0.5);
               setPos(mapToParent(0, -(speed)));
               if (turn == true){
                   if((turn_right == true) && (rotation() == (angle - 90))){
                       Rotation_Right();
                       if (angle == 270){
                           angle = 0;
                       } else {
                           angle += 90;
                       }
                   }
                   if((turn_right == false) && (rotation() == angle_exit_t)){
                       Rotation_Right();
                       if (angle == 0){
                           angle = 270;
                       } else {
                           angle -= 90;
                       }
                   }
                   turn = false;
               } else {
                   if (rotation() == angle_exit_f) {
                       Rotation_Right();
                   }
               }
           } else {
               setPos(mapToParent(0, -(speed)));
           }
           if (angle == 0){
               if ((turn_in == false) && (this->pos().y() >= 90) && (this->pos().y() <= 110)){
                   Rotation_Right();
               }
               if ((this->pos().y() >= -310) && (this->pos().y() <= -300)){
                   delete this;
               }
           }
           if (angle == 90){
               if ((this->pos().x() >= 340) && (this->pos().x() <= 350)){
                   delete this;
               }
           }
           if (angle == 180){
               if ((this->pos().y() >= 300) && (this->pos().y() <= 310)){
                   delete this;
               }
           }
           if (angle == 270){
               if ((this->pos().x() >= -350) && (this->pos().x() <= -340)){
                   delete this;
               }
           }*/
       } else {
           if (angle == 0){
               if (turn == true){
                   if ((turn_right == true) && (this->pos().y() >= 30) && (this->pos().y() <= 50)){
                       Rotation_Right();
                       //angle += 90;
                       //turn = false;
                   }
                   if ((turn_right == false) && (this->pos().y() >= -30) && (this->pos().y() <= -10)){
                       Rotation_Left();
                       //angle = 270;
                       //turn = false;
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
                   if ((turn_right == true) && (this->pos().x() >= -45) && (this->pos().x() <= -25))
                   {
                       Rotation_Right();
                       //angle += 90;
                       //turn = false;
                   }
                   if ((turn_right == false) && (this->pos().x() >= 15) && (this->pos().x() <= 35))
                   {
                       Rotation_Left();
                       //angle -= 90;
                       //turn = false;
                   }
               }
               if ((this->pos().x() > -160) && (this->pos().x() < -150) && ((tr_l->color == false) || ((tr_l->yellow >= 3) && (tr_l->yellow <= 4))))
               {
                   setPos(mapToParent(0, 0));
               } else {
                   setPos(mapToParent(0, -(speed)));
               }
               if ((this->pos().x() >= 340) && (this->pos().x() <= 350)){
                   tr_l->Delete_Car();
                   delete this;
               }
           }
           if (angle == 180){
               if (turn == true){
                   if ((turn_right == true) && (this->pos().y() >= -40) && (this->pos().y() <= -50))
                   {
                       Rotation_Right();
                       //angle += 90;
                       //turn = false;
                   }
                   if ((turn_right == false) && (this->pos().y() >= 20) && (this->pos().y() <= 40))
                   {
                       Rotation_Left();
                       //angle -= 90;
                       //turn = false;
                   }
               }
               if ((this->pos().y() > -170) && (this->pos().y() < -160) && ((tr_l->color == false) || ((tr_l->yellow >= 3) && (tr_l->yellow <= 4))))
               {
                   setPos(mapToParent(0, 0));
               } else {
                   setPos(mapToParent(0, -(speed)));
               }
               if ((this->pos().y() >= 300) && (this->pos().y() <= 310)){
                   tr_l->Delete_Car();
                   delete this;
               }
           }
           if (angle == 270)
           {
               if (turn == true){
                   if ((turn_right == true) && (this->pos().x() >= 25) && (this->pos().x() <= 45))
                   {
                       Rotation_Right();
                       //angle = 0;
                       //turn = false;
                   }
                   if ((turn_right == false) && (this->pos().x() >= -35) && (this->pos().x() <= -15))
                   {
                       Rotation_Left();
                       //angle -= 90;
                       //turn = false;
                   }
               }
               if ((this->pos().x() > 150) && (this->pos().x() < 160) && ((tr_l->color == false) || ((tr_l->yellow >= 3) && (tr_l->yellow <= 4))))
               {
                   setPos(mapToParent(0, 0));
               } else {
                   setPos(mapToParent(0, -(speed)));
               }
               if ((this->pos().x() >= -350) && (this->pos().x() <= -340)){
                   tr_l->Delete_Car();
                   delete this;
               }
           }
       }
}

QRectF Car::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-10 - adjust, -20 - adjust,
                      20 + adjust, 40 + adjust);
}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(color);
    painter->drawRect(-10, -20, 20, 40);
}


