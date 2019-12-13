#include "tr_light.h"

Tr_Light::Tr_Light(bool _light, int _angle, int timer_light)
: color(_light), angle(_angle)
{
    if ((angle == 0) || (angle == 180)){
        this->setFixedSize(51, 131);
    } else {
        this->setFixedSize(131, 51);
    }
    this->rect.setCoords(110, 110, 100, 200);
    _interval = 4000;
    crash = false;
    yellow = 1;
    this->timer_yellow = new QTimer(this);
    connect(timer_yellow, &QTimer::timeout, this, &Tr_Light::Yellow);
    timer_yellow->start(timer_light/4);
    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Tr_Light::ChangeColor);
    timer->start(timer_light);
}

void Tr_Light::Change_Timer_Create_Car(int time)
{
    _interval = 1000*time;
}
void Tr_Light::Yellow()
{
    ++yellow;
    update();
}
void Tr_Light::ChangeColor()
{
    color = !color;
    yellow = 0;
    update();
}

void Tr_Light::mousePressEvent(QMouseEvent *)
{
    color = !color;
    crash = true;
    update();
}

void Tr_Light::paintEvent(QPaintEvent*){
    painter.begin(this);
    if (angle == 0){
        painter.drawRect(0, 0, 50, 130);
        painter.setBrush(color == true ? Qt::darkRed : Qt::red);
        painter.drawEllipse(QRectF(10, 10, 30, 30));
        painter.setBrush((yellow >= 3)&& (yellow <= 4) ? Qt::yellow : Qt::darkYellow);
        painter.drawEllipse(QRectF(10, 50, 30, 30));
        painter.setBrush(color == true ? Qt::green : Qt::darkGreen);
        painter.drawEllipse(QRectF(10, 90, 30, 30));
    }
    if(angle == 90){
        painter.drawRect(0, 0, 130, 50);
        painter.setBrush(color == true ? Qt::green : Qt::darkGreen);
        painter.drawEllipse(QRectF(10, 10, 30, 30));
        painter.setBrush((yellow >= 3)&& (yellow <= 4) ? Qt::yellow : Qt::darkYellow);
        painter.drawEllipse(QRectF(50, 10, 30, 30));
        painter.setBrush(color == true ? Qt::darkRed : Qt::red);
        painter.drawEllipse(QRectF(90, 10, 30, 30));
    }
    if (angle == 180){
        painter.drawRect(0, 0, 50, 130);
        painter.setBrush(color == true ? Qt::green : Qt::darkGreen);
        painter.drawEllipse(QRectF(10, 10, 30, 30));
        painter.setBrush((yellow >= 3)&& (yellow <= 4) ? Qt::yellow : Qt::darkYellow);
        painter.drawEllipse(QRectF(10, 50, 30, 30));
        painter.setBrush(color == true ? Qt::darkRed : Qt::red);
        painter.drawEllipse(QRectF(10, 90, 30, 30));
    }
    if(angle == 270){
        painter.drawRect(0, 0, 130, 50);
        painter.setBrush(color == true ? Qt::darkRed : Qt::red);
        painter.drawEllipse(QRectF(10, 10, 30, 30));
        painter.setBrush((yellow >= 3)&& (yellow <= 4) ? Qt::yellow : Qt::darkYellow);
        painter.drawEllipse(QRectF(50, 10, 30, 30));
        painter.setBrush(color == true ? Qt::green : Qt::darkGreen);
        painter.drawEllipse(QRectF(90, 10, 30, 30));
    }
    painter.end();
}
