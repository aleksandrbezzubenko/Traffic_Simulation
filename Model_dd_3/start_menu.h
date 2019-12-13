#ifndef START_MENU_H
#define START_MENU_H

#include <QDialog>
#include "car.h"
#include "light_car.h"
#include "hight_car.h"
#include "tr_light.h"
#include <QApplication>
#include <QtWidgets>
#include <QPixmap>
#include <QBrush>
#include <QLabel>
#include <QImage>
#include <QStyleOption>
#include <QPalette>
#include <chrono>
#include <thread>
#include <functional>
#include <random>
#include <ctime>

namespace Ui {
class Start_Menu;
}

class Start_Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Start_Menu(QWidget *parent = 0);
    ~Start_Menu();
    QGraphicsScene *scene;
    QGraphicsView *view;
    static void Create_Car_With_Trl(Tr_Light *trl, QGraphicsScene *scene, int _limite_type_car);
    static void Create_Car_Without_Trl(QGraphicsScene *scene, int _limite_type_car);
    static void timer_start_With_Trl(unsigned int interval, Tr_Light *trl, QGraphicsScene *scene, int _limite_type_car);
    static void timer_start_Without_Trl(unsigned int interval, QGraphicsScene *scene, int _limite_type_car);
    bool Circular_motion()
    {
        return circular_motion;
    }
private:
    int concentration_car = 5500;
    int timer_trl = 5000;
    int type_car = 50;
    bool circular_motion;
private slots:
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_pushButton_clicked();
    void on_horizontalSlider_3_valueChanged(int value);
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
private:
    Ui::Start_Menu *ui;
};

#endif // START_MENU_H
