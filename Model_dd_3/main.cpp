#include "car.h"
#include "tr_light.h"
#include <QApplication>
#include <QtWidgets>
#include <QPixmap>
#include <QBrush>
#include <QLabel>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QGraphicsScene *scene = new QGraphicsScene(-300, -300, 600, 600);

    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    int CarCount = 20;
    Tr_Light *trl_1 = new Tr_Light(false);
    trl_1->setGeometry(100, -150, 100, 100);
    scene->addWidget(trl_1);
    //QTimer *create_car_timer = new QTimer;
    //QObject::connect(create_car_timer, &QTimer::timeout, scene, &Car::Create_Car);
    //Car::Create_Car(trl_1, scene);
    //create_car_timer->start(1000);
    for (int i = 0; i < CarCount; ++i) {
        bool turn = false;
        if (i % 2 == 0)
        {
            turn = true;
        }
        bool turn_right = false;
        if (i % 4)
        {
            turn_right = true;
        }
        Car *car = new Car(trl_1->color, true, turn, turn_right, 270);
        car->setPos((i*100 - 100), 0);
        trl_1->Push_Car(car);
        scene->addItem(car);
        }
    Tr_Light *trl_2 = new Tr_Light(true);
    trl_2->setGeometry(50, 100, 100, 100);
    scene->addWidget(trl_2);
    for (int i = 0; i < CarCount; ++i) {
        bool turn = false;
        if (i % 2 == 0)
        {
            turn = true;
        }
        bool turn_right = false;
        if (i % 4)
        {
            turn_right = true;
        }
        Car *car = new Car(trl_2->color, false, turn, turn_right, 0);
        car->setPos(0, (i*100 + 200));
        trl_2->Push_Car(car);
        scene->addItem(car);
        }

    QGraphicsView view(scene);
        view.setRenderHint(QPainter::Antialiasing);
        view.setBackgroundBrush(QColor(230, 200, 167));

        view.setCacheMode(QGraphicsView::CacheBackground);
            view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
            view.setDragMode(QGraphicsView::ScrollHandDrag);

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
