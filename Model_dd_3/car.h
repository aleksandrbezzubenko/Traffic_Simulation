#ifndef CAR_H
#define CAR_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QPainter>
#include <random>
#include <ctime>
#include <chrono>
#include <thread>
#include <ui_car.h>
//#include "zagolovok.h"
//#include <tr_light.h>

class Tr_Light;

class Car : public QGraphicsItem
{
public:
    Car(Tr_Light *trl, int _turn, bool _circular_motion, QGraphicsScene *_scene);
    Car(int angle_car, int _turn, bool _circular_motion, QGraphicsScene *_scene);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void Change_Light();
    void Game_over(){
        QGraphicsPixmapItem *item_game_over = new QGraphicsPixmapItem(QPixmap("/home/hp/Model_dd_3/images/Game_over_1.jpg"));
        item_game_over->setPos(-150, -150);
        scene->addItem(item_game_over);
        game_over = true;
    }
    void timer_go(QGraphicsScene *_scene, Car *car){
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
    void Rotation_Right()
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
            turn_in = !turn_in;
        } else {
            //turn_in = false;
        }
    }
    void Rotation_Left()
    {
        /*std::thread([this]() {
            int angle = 85;
            while (angle >= 0){
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                this->setRotation(rotation() - 5);
                angle -= 5;
            }
        }).detach();*/
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
    qreal speed;
    QColor color;
    Tr_Light *tr_l;
protected:
    void advance(int step) override;
public slots:
    /*void Turn_right()
    {
        Rotation_Right();
        angle += 90;
    }*/
private:

    QGraphicsScene *scene;
    QTimer *timer_game_over;
    bool circular_motion;
    bool game_over;
    bool turn;
    bool turn_right;
    bool turn_in;
    int angle;
    int angle_1;
    float angle_in_circular_motoin;
    int angle_exit_t;
    int angle_exit_f;
    int borders_h;
    int borders_w;
};

#endif // CAR_H
