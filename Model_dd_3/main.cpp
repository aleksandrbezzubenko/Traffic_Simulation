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


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QGraphicsScene *scene = new QGraphicsScene(-300, -300, 600, 600);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    QGraphicsView *view = new QGraphicsView(scene);
    Start_Menu *menu = new Start_Menu;
    menu->scene = scene;
    menu->view = view;
        view->setRenderHint(QPainter::Antialiasing);
        //if (menu->Circular_motion()){

        //} else {
            //view->setBackgroundBrush(QPixmap("/home/hp/Model_dd_3/images/perek_circular_motion_1.png"));
        //}
        view->setCacheMode(QGraphicsView::CacheBackground);
          view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
            view->setDragMode(QGraphicsView::ScrollHandDrag);
            view->setAutoFillBackground(true);
            view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Model_dd"));
            #if defined(Q_WS_S60) || defined(Q_WS_MAEMO_5) || defined(Q_WS_SIMULATOR)
                view->showMaximized();
            #else
                view->resize(1000, 1000);
                view->show();
                menu->show();
            #endif
                QTimer timer;
                QObject::connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
                timer.start(1000 / 53);
    return app.exec();
}
