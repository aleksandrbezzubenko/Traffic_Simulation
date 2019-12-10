#include "car.h"
#include "light_car.h"
#include "hight_car.h"
#include "start_menu.h"
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


/*void Create_Car(Tr_Light *trl, QGraphicsScene *scene)
{
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<> uid(0, 10);
    std::mt19937 gen_1(time(0));
    std::uniform_int_distribution<> uid_1(0, 10);
    int turn = uid(gen);
    int type_car = uid_1(gen_1);
    if ((trl->angle == 0) || (trl->angle == 90)){
        ++turn;
    }
    if (type_car < 8){
        Light_Car *car = new Light_Car(trl, turn, scene);
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
        Hight_Car *car = new Hight_Car(trl, turn, scene);
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

void timer_start(unsigned int interval, Tr_Light *trl, QGraphicsScene *scene)
{
    std::thread([trl, scene, interval]() {
        while (true)
        {
            Create_Car(trl, scene);
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }).detach();
}*/

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QGraphicsScene *scene = new QGraphicsScene(-300, -300, 600, 600);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    Start_Menu *menu = new Start_Menu;
    menu->scene = scene;
    /*QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(1, 10);
    slider->setGeometry(100, -150, 200, 20);
    slider->setValue(5);
    //Tr_Light::connect(slider, SIGNAL(valueChanged(int)), lcdAL, SLOT(display(int)));
    //scene->addWidget(slider);
    Tr_Light *trl_1 = new Tr_Light(false, 270);
    trl_1->setGeometry(100, -130, 100, 150);
    Tr_Light::connect(slider, SIGNAL(valueChanged(int)), trl_1, SLOT(Change_Timer_Create_Car(int)));
    scene->addWidget(trl_1);
    Tr_Light::timer_start(trl_1->_interval, trl_1, scene);
    //timer_start(4000, trl_1, scene, true, 270);
    Tr_Light *trl_2 = new Tr_Light(true, 0);
    trl_2->setGeometry(80, 100, 100, 100);
    Tr_Light::connect(slider, SIGNAL(valueChanged(int)), trl_2, SLOT(Change_Timer_Create_Car(int)));
    scene->addWidget(trl_2);
    Tr_Light::timer_start(trl_2->_interval, trl_2, scene);
    Tr_Light *trl_3 = new Tr_Light(false, 90);
    trl_3->setGeometry(-220, 80, 100, 150);
    //Tr_Light::connect(slider, SIGNAL(&valueChanged(int)), trl_3, SLOT(&Tr_Light::Change_Timer_Create_Car(int s)));
    //Tr_Light::connect(slider, &QSlider::valueChanged(int), this, &Tr_Light::Change_Timer_Create_Car(int));
    scene->addWidget(trl_3);
    Tr_Light::timer_start(trl_3->_interval, trl_3, scene);
    Tr_Light *trl_4 = new Tr_Light(true, 180);
    trl_4->setGeometry(-140, -210, 100, 150);
    Tr_Light::connect(slider, SIGNAL(valueChanged(int)), trl_4, SLOT(Change_Timer_Create_Car(int)));
    scene->addWidget(trl_4);
    Tr_Light::timer_start(trl_4->_interval, trl_4, scene);*/
    QGraphicsView view(scene);
        view.setRenderHint(QPainter::Antialiasing);
        //if (menu->Circular_motion()){

        //} else {
            view.setBackgroundBrush(QPixmap("/home/hp/Model_dd_3/images/perek_circular_motion.jpg"));
        //}
        view.setCacheMode(QGraphicsView::CacheBackground);
          view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
            view.setDragMode(QGraphicsView::ScrollHandDrag);
            view.setAutoFillBackground(true);
            view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Model_dd"));
            #if defined(Q_WS_S60) || defined(Q_WS_MAEMO_5) || defined(Q_WS_SIMULATOR)
                view.showMaximized();
            #else
                view.resize(1000, 1000);
                view.show();
                menu->show();
            #endif
                QTimer timer;
                QObject::connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
                timer.start(1000 / 53);
    return app.exec();
}
