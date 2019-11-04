#include "traffic_light.h"

Traffic_Light::Traffic_Light()
{
    this->setFixedSize(51, 91);
    this->rect.setCoords(110, 110, 100, 200);
    this->color = false;
}

void Traffic_Light::mousePressEvent(QMouseEvent *)
{
    color = !color;
    update();
}

void Traffic_Light::paintEvent(QPaintEvent*){
    painter.begin(this);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, 50, 90);
    painter.setBrush(color == true ? Qt::darkRed : Qt::red);
    painter.drawEllipse(QRectF(10, 10, 30, 30));
    painter.setBrush(color == true ? Qt::green : Qt::darkGreen);
    painter.drawEllipse(QRectF(10, 50, 30, 30));
    painter.end();
}
