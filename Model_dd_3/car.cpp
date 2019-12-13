#include "car.h"
#include "tr_light.h"
#include "ui_car.h"
#include <QtWidgets>
#include <QRect>
#include <QPainter>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

Car::Car(Tr_Light *trl, int _turn, bool _circular_motion, QGraphicsScene *_scene, float _koef_type_car)
    : speed(0), tr_l(trl), koef_type_car(_koef_type_car), angle(tr_l->angle), game_over(false), circular_motion(_circular_motion), turn_in(false), scene(_scene),color(qrand() % 256, qrand() % 256, qrand() % 256)
{
    borders_h = 30;
    borders_w = 70;
    speed = 1.5*koef_type_car;
    angle_in_circular_motoin = 0.75*koef_type_car;
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

Car::Car(int angle_car, int _turn, bool _circular_motion, QGraphicsScene *_scene, float _koef_type_car)
    : speed(0), angle_in_circular_motoin(0.75), koef_type_car(_koef_type_car), angle(angle_car), game_over(false), circular_motion(_circular_motion), turn_in(false), scene(_scene),color(qrand() % 256, qrand() % 256, qrand() % 256)
{
    speed = 1.5;
    angle_in_circular_motoin = 0.75;
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
    sum_angle_in_circular_motoin = 0;
    angle_1 = 0;
    setRotation(angle);
}

void Car::Rotation_in_out_circular(int num)
{
    setRotation(rotation() + 3);
    angle_1 += 3;
    if (angle_1 == num){
        angle_1 = 0;

        if (turn_in){
            if (turn){
                if (turn_right){
                    if (angle == 270){
                        angle = 0;
                    } else {
                        angle += 90;
                    }
                } else {
                    if (angle == 0){
                        angle = 270;
                    } else {
                        angle -= 90;
                    }
                }
            }
        }
        turn_in = !turn_in;
    }
}

void Car::Rotation_Right()
{
    setRotation(rotation() + 5);
    angle_1 += 5;
    if (angle_1 == 90){
        if (!circular_motion){
            if (angle == 270){
                angle = 0;
            } else {
                angle += 90;
            }
            turn = false;
        }
        angle_1 = 0;
    }
}
void Car::Rotation_Left()
{
    setRotation(rotation() - 5);
    angle_1 -= 5;
    if (angle_1 == 0){
        if (angle == 0){
            angle = 270;
        } else {
            angle -= 90;
        }
        turn = false;
        angle_1 = 90;
    }
}

void Car::Game_over(){
    QGraphicsPixmapItem *item_game_over = new QGraphicsPixmapItem(QPixmap("/home/hp/Model_dd_3/images/Game_over_1.jpg"));
    item_game_over->setPos(-150, -150);
    scene->addItem(item_game_over);
    game_over = true;
}
void Car::timer_go(QGraphicsScene *_scene, Car *car){
    std::thread([_scene, car]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        QGraphicsPixmapItem *item_buum = new QGraphicsPixmapItem(QPixmap("/home/hp/Model_dd_3/images/buum.jpg"));
        item_buum->setPos(car->pos().x() - 37, car->pos().y() - 37);
        _scene->addItem(item_buum);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        QGraphicsPixmapItem *item_game_over = new QGraphicsPixmapItem(QPixmap("/home/hp/Model_dd_3/images/Game_over_1.jpg"));
        item_game_over->setPos(-200, -200);
        delete item_buum;
        _scene->addItem(item_game_over);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        exit(0);
    }).detach();
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
            borders_h = 55;
            borders_w = 70;
        }
    }

    const QList<QGraphicsItem *> dangerMice = scene->items(QPolygonF()
                               << mapToScene(0, 0)
                               << mapToScene(-borders_h, -borders_w)
                               << mapToScene(borders_h, -borders_w));
    float speed_copy = speed;
    float angle_in_circular_motoin_copy = angle_in_circular_motoin;
       for (const QGraphicsItem *car : dangerMice) {
           if (car == this){
               continue;
           } else {
               speed_copy = 0;
               angle_in_circular_motoin_copy = 0;
               if ((!circular_motion && (this->pos().y() < 100) && (this->pos().y() > -130) && (this->pos().x() > -120) && (this->pos().x() < 110) && (angle_1 == 0))){
                   turn_right = true;
               }
           }
           if (!circular_motion){
               if ((tr_l->crash == false) || (tr_l->crash && ((this->pos().y() > 100) || (this->pos().y() < -130) ||
                                                          (this->pos().x() < -120) || (this->pos().x() > 110)))){
                   speed_copy = 0;
               }
           }
       }
       if (!scene->collidingItems(this).isEmpty() && (this->pos().y() < 100) &&
               (this->pos().y() > -130) && (this->pos().x() > -120) && (this->pos().x() < 110)){
           if (!game_over && tr_l->crash) {
               timer_go(scene, this);
               game_over = true;
           }
           tr_l->crash = false;
           speed_copy = 0;
           update();
       }
       if (circular_motion){
           setPos(mapToParent(0, -(speed_copy)));
           if (turn_in == true){
               setRotation(rotation() - angle_in_circular_motoin_copy);
               sum_angle_in_circular_motoin += angle_in_circular_motoin_copy;
               if (turn == true){
                   if ((sum_angle_in_circular_motoin >= 35) && (turn_right == true)){
                       Rotation_in_out_circular(87);
                   } else if ((sum_angle_in_circular_motoin >= 200) && (turn_right == false)){
                       Rotation_in_out_circular(66);
                   }
               } else {
                   if (sum_angle_in_circular_motoin >= 116){
                       Rotation_in_out_circular(75);
                   }
               }
           }
           if (angle == 0){
               if ((turn_in == false) && (this->pos().y() >= 100) && (this->pos().y() <= 130)){
                   Rotation_in_out_circular(60);
               }
           }
           if (angle == 90){
               if ((turn_in == false) && (this->pos().x() > -140) && (this->pos().x() < -110)){
                   Rotation_in_out_circular(60);
               }
           }
           if (angle == 180){
               if ((turn_in == false) && (this->pos().y() >= -140) && (this->pos().y() <= -110)){
                   Rotation_in_out_circular(60);
               }
           }
           if (angle == 270){
               if ((turn_in == false) && (this->pos().x() > 100) && (this->pos().x() < 130)){
                   Rotation_in_out_circular(60);
               }
           }
       } else {
           if (angle == 0){
               if (turn == true){
                   if ((turn_right == true) && (this->pos().y() >= 20) && (this->pos().y() <= 60)){
                       Rotation_Right();
                   }
                   if ((turn_right == false) && (this->pos().y() >= -40) && (this->pos().y() <= -20)){
                       Rotation_Left();
                   }
               }
               if ((this->pos().y() > 140) && (this->pos().y() < 150) && ((tr_l->color == false) || ((tr_l->yellow >= 3) && (tr_l->yellow <= 4)))) {
                   setPos(mapToParent(0, 0));
               } else {
                   setPos(mapToParent(0, -(speed_copy)));
               }
           }
           if (angle == 90) {
               if (turn == true){
                   if ((turn_right == true) && (this->pos().x() >= -55) && (this->pos().x() <= -15)) {
                       Rotation_Right();
                   }
                   if ((turn_right == false) && (this->pos().x() >= 15) && (this->pos().x() <= 35)) {
                       Rotation_Left();
                   }
               }
               if ((this->pos().x() > -160) && (this->pos().x() < -150) && ((tr_l->color == false) || ((tr_l->yellow >= 3) && (tr_l->yellow <= 4)))) {
                   setPos(mapToParent(0, 0));
               } else {
                   setPos(mapToParent(0, -(speed_copy)));
               }
           }
           if (angle == 180){
               if (turn == true){
                   if ((turn_right == true) && (this->pos().y() >= -20) && (this->pos().y() <= -60)) {
                       Rotation_Right();
                   }
                   if ((turn_right == false) && (this->pos().y() >= 30) && (this->pos().y() <= 50)) {
                       Rotation_Left();
                   }
               }
               if ((this->pos().y() > -170) && (this->pos().y() < -160) && ((tr_l->color == false) || ((tr_l->yellow >= 3) && (tr_l->yellow <= 4)))) {
                   setPos(mapToParent(0, 0));
               } else {
                   setPos(mapToParent(0, -(speed_copy)));
               }
           }
           if (angle == 270) {
               if (turn == true){
                   if ((turn_right == true) && (this->pos().x() >= 15) && (this->pos().x() <= 55)) {
                       Rotation_Right();
                   }
                   if ((turn_right == false) && (this->pos().x() >= -35) && (this->pos().x() <= -15)) {
                       Rotation_Left();
                   }
               }
               if ((this->pos().x() > 150) && (this->pos().x() < 160) && ((tr_l->color == false) || ((tr_l->yellow >= 3) && (tr_l->yellow <= 4)))) {
                   setPos(mapToParent(0, 0));
               } else {
                   setPos(mapToParent(0, -(speed_copy)));
               }
           }
       }
       if (angle == 0){
           if ((this->pos().y() >= -510) && (this->pos().y() <= -500)){
               delete this;
           }
       } else if (angle == 90){
           if ((this->pos().x() >= 540) && (this->pos().x() <= 550)){
               delete this;
           }
       } else if (angle == 180){
           if ((this->pos().y() >= 500) && (this->pos().y() <= 510)){
               delete this;
           }
       } else if (angle == 270){
           if ((this->pos().x() >= -550) && (this->pos().x() <= -540)){
               delete this;
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


