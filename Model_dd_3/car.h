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

class Tr_Light;

class Car : public QGraphicsItem
{
public:
    Car(Tr_Light *trl, int _turn, bool _circular_motion, QGraphicsScene *_scene, float _koef_type_car);
    Car(int angle_car, int _turn, bool _circular_motion, QGraphicsScene *_scene, float _koef_type_car);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void Change_Light();
    void Game_over();
    void timer_go(QGraphicsScene *_scene, Car *car);
    void Rotation_in_out_circular(int num);
    void Rotation_Right();
    void Rotation_Left();
    qreal speed;
    QColor color;
    Tr_Light *tr_l;
protected:
    void advance(int step) override;
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
    float sum_angle_in_circular_motoin;
    float koef_type_car;
    int angle_exit_t;
    int angle_exit_f;
    int borders_h;
    int borders_w;
};

#endif // CAR_H
