#include "car.h"
//#include "traffic_light.h"
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


void Create_Car(Tr_Light *trl, QGraphicsScene *scene)
{
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<> uid(0, 10);
    int turn = uid(gen);
    if ((trl->angle == 0) || (trl->angle == 90)){
        ++turn;
    }
    Car *car = new Car(trl, turn);
    if (trl->angle == 0){
        car->setPos(30, 600);
    }
    if (trl->angle == 90){
        car->setPos(-600, 30);
    }
    if (trl->angle == 180){
        car->setPos(-40, -600);
    }
    if (trl->angle == 270){
        car->setPos(600, -30);
    }
    trl->Push_Car(car);
    scene->addItem(car);
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
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QGraphicsScene *scene = new QGraphicsScene(-300, -300, 600, 600);
    bool pzdc = false;
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    Tr_Light *trl_1 = new Tr_Light(false, 270, pzdc);
    trl_1->setGeometry(100, -130, 100, 150);
    scene->addWidget(trl_1);
    timer_start(4000, trl_1, scene);
    //timer_start(4000, trl_1, scene, true, 270);
    Tr_Light *trl_2 = new Tr_Light(true, 0, pzdc);
    trl_2->setGeometry(80, 100, 100, 100);
    scene->addWidget(trl_2);
    timer_start(4000, trl_2, scene);
    Tr_Light *trl_3 = new Tr_Light(false, 90, pzdc);
    trl_3->setGeometry(-220, 80, 100, 150);
    scene->addWidget(trl_3);
    timer_start(4000, trl_3, scene);
    Tr_Light *trl_4 = new Tr_Light(true, 180, pzdc);
    trl_4->setGeometry(-140, -210, 100, 150);
    scene->addWidget(trl_4);
    timer_start(4000, trl_4, scene);
    //if ((trl_1->pzdc == true) || (trl_2->pzdc == true) || (trl_3->pzdc == true) || (trl_4->pzdc == true)){
      //  QGraphicsPixmapItem item(QPixmap("/home/hp/Model_dd_3/images/buum.jpg"));
      //  scene->addItem(&item);
    //}
    QGraphicsView view(scene);

        view.setRenderHint(QPainter::Antialiasing);
        view.setBackgroundBrush(QPixmap("/home/hp/Model_dd_3/images/perek_n.jpg"));
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
            #endif
                QTimer timer;
                QObject::connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
                timer.start(1000 / 53);

    return app.exec();
}
