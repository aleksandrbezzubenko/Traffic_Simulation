#include "tr_light.h"

Tr_Light::Tr_Light(bool light)
{
    this->setFixedSize(51, 91);
    this->rect.setCoords(110, 110, 100, 200);
    this->color = light;
    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Tr_Light::ChangeColor);
    timer->start(4000);
}

void Tr_Light::Push_Car(Car* car)
{
    cars.push_back(car);
}

void Tr_Light::mousePressEvent(QMouseEvent *)
{
    color = !color;
    for(int i = 0; i < cars.size(); ++i) {
        cars[i]->Change_Light();
    }
    update();
}

void Tr_Light::paintEvent(QPaintEvent*){
    painter.begin(this);
    painter.drawRect(0, 0, 50, 90);
    painter.setBrush(color == true ? Qt::darkRed : Qt::red);
    painter.drawEllipse(QRectF(10, 10, 30, 30));
    painter.setBrush(color == true ? Qt::green : Qt::darkGreen);
    painter.drawEllipse(QRectF(10, 50, 30, 30));
    painter.end();
}
