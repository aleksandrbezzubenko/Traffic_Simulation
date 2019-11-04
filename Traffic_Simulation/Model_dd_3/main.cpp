#include "car.h"
#include "traffic_light.h"
#include <QApplication>
#include <QtWidgets>
#include <QLabel>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QGraphicsScene scene(-300, -300, 600, 600);

    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    int CarCount = 10;
    for (int i = 0; i < CarCount; ++i) {
            Car *car = new Car;
            car->setPos(::sin((i * 6.28) / CarCount) * 200,
                          ::cos((i * 6.28) / CarCount) * 200);
            car->setPos(i*100, 150);
            scene.addItem(car);
        }
    Traffic_Light *trl = new Traffic_Light;
    trl->setGeometry(100, 0, 100, 100);
    scene.addWidget(trl);
    QGraphicsView view(&scene);
        view.setRenderHint(QPainter::Antialiasing);
        view.setBackgroundBrush(QColor(230, 200, 167));

        view.setCacheMode(QGraphicsView::CacheBackground);
            view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
            view.setDragMode(QGraphicsView::ScrollHandDrag);

            view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Model_dd"));
            #if defined(Q_WS_S60) || defined(Q_WS_MAEMO_5) || defined(Q_WS_SIMULATOR)
                view.showMaximized();
            #else
                view.resize(1000, 500);
                view.show();
            #endif
                QTimer timer;
                QObject::connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
                timer.start(1000 / 33);

    return app.exec();
}
