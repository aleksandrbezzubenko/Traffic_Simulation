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

void Tr_Light::Push_Car(Car* car)
{
    cars.push_back(car);
}

void Tr_Light::Delete_Car()
{
    cars.pop_front();
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

void Tr_Light::Create_Car(Tr_Light *trl, QGraphicsScene *scene, int _limite_type_car)
{
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<> uid(0, 10);
    std::mt19937 gen_1(time(0));
    std::uniform_int_distribution<> uid_1(0, 100);
    int turn = uid(gen);
    int type_car = uid_1(gen_1);
    if ((trl->angle == 0) || (trl->angle == 90)){
        ++turn;
    }
    if (type_car < _limite_type_car){
        Light_Car *car = new Light_Car(trl, turn, false, scene);
        if (trl->angle == 0){
            car->setPos(30, 1000);
        }
        if (trl->angle == 90){
            car->setPos(-1000, 30);
        }
        if (trl->angle == 180){
            car->setPos(-40, -1000);
        }
        if (trl->angle == 270){
            car->setPos(1000, -30);
        }
        trl->Push_Car(car);
        scene->addItem(car);
    } else {
        Hight_Car *car = new Hight_Car(trl, turn, false, scene);
        if (trl->angle == 0){
            car->setPos(30, 1000);
        }
        if (trl->angle == 90){
            car->setPos(-1000, 30);
        }
        if (trl->angle == 180){
            car->setPos(-40, -1000);
        }
        if (trl->angle == 270){
            car->setPos(1000, -30);
        }
        trl->Push_Car(car);
        scene->addItem(car);
    }
}

void Tr_Light::timer_start(unsigned int interval, Tr_Light *trl, QGraphicsScene *scene, int _limite_type_car)
{
    std::thread([trl, scene, interval, _limite_type_car]() {
        while (true)
        {
            Create_Car(trl, scene, _limite_type_car);
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }).detach();
}
