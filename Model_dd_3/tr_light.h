#ifndef TR_LIGHT_H
#define TR_LIGHT_H

#include <QPaintEvent>
#include <QPoint>
#include <QRect>
#include <QTimer>
#include <QPainter>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QList>
#include <cmath>
#include <vector>
#include <QVector>


//#include "zagolovok.h"
#include "car.h"

class Tr_Light : public QWidget
{
public:
    bool color;
    Tr_Light(bool light);
    QPainter painter;
    QRect rect;
    QTimer *timer;
    QVector<Car*> cars;
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *);
    void Push_Car(Car *car);
    //void ChangeColor();
    //void mouseDoubleClickEvent(QMouseEvent *);
public slots:
    void ChangeColor()
    {
        color = !color;
        for(int i = 0; i < cars.size(); ++i) {
            cars[i]->Change_Light();
        }
        update();
    }
};
#endif // TR_LIGHT_H
