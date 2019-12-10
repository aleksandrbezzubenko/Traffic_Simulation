#include "start_menu.h"
#include "ui_start_menu.h"

Start_Menu::Start_Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Start_Menu)
{
    ui->setupUi(this);
}

Start_Menu::~Start_Menu()
{
    delete ui;
}

void Start_Menu::Create_Car_Without_Trl(QGraphicsScene *scene, int _limite_type_car)
{
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<> uid(0, 10);
    std::mt19937 gen_1(time(0));
    std::uniform_int_distribution<> uid_1(0, 100);
    std::mt19937 gen_2(time(0));
    std::uniform_int_distribution<> uid_2(0, 80);
    int turn = uid(gen);
    int type_car = uid_1(gen_1);
    int angle_car = uid_2(gen_2);

    if ((angle_car > 0) && (angle_car <= 20)){
        angle_car = 0;
    } else if ((angle_car > 20) && (angle_car <= 40)){
        angle_car = 90;
    } else if ((angle_car > 40) && (angle_car <= 60)){
        angle_car = 180;
    } else if ((angle_car > 60) && (angle_car <= 80)){
        angle_car = 270;
    }
    if ((angle_car == 0) || (angle_car == 90)){
        ++turn;
    }
    if (type_car < _limite_type_car){
        Light_Car *car = new Light_Car(angle_car, turn, true, scene);
        if (angle_car == 0){
            car->setPos(30, 1000);
        }
        if (angle_car == 90){
            car->setPos(-1000, 30);
        }
        if (angle_car == 180){
            car->setPos(-40, -1000);
        }
        if (angle_car == 270){
            car->setPos(1000, -30);
        }
        scene->addItem(car);
    } else {
        Hight_Car *car = new Hight_Car(angle_car, turn, true, scene);
        if (angle_car == 0){
            car->setPos(30, 1000);
        }
        if (angle_car == 90){
            car->setPos(-1000, 30);
        }
        if (angle_car == 180){
            car->setPos(-40, -1000);
        }
        if (angle_car == 270){
            car->setPos(1000, -30);
        }
        scene->addItem(car);
    }
}

void Start_Menu::Create_Car_With_Trl(Tr_Light *trl, QGraphicsScene *scene, int _limite_type_car)
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

void Start_Menu::timer_start_With_Trl(unsigned int interval, Tr_Light *trl, QGraphicsScene *scene, int _limite_type_car)
{
    std::thread([trl, scene, interval, _limite_type_car]() {
        while (true)
        {
            Start_Menu::Create_Car_With_Trl(trl, scene, _limite_type_car);
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }).detach();
}

void Start_Menu::timer_start_Without_Trl(unsigned int interval, QGraphicsScene *scene, int _limite_type_car)
{
    std::thread([scene, interval, _limite_type_car]() {
        while (true)
        {
            Start_Menu::Create_Car_Without_Trl(scene, _limite_type_car);
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }).detach();
}

void Start_Menu::on_horizontalSlider_valueChanged(int value)
{
    timer_trl = value;
}

void Start_Menu::on_horizontalSlider_2_valueChanged(int value)
{
    concentration_car = value;
}

void Start_Menu::on_horizontalSlider_3_valueChanged(int value)
{
    type_car = value;
}

void Start_Menu::on_pushButton_clicked()
{
    if (circular_motion){
        Start_Menu::timer_start_Without_Trl(concentration_car, scene, type_car);
        hide();
    } else {
        Tr_Light *trl_1 = new Tr_Light(false, 270, timer_trl);
        trl_1->setGeometry(100, -130, 100, 150);
        scene->addWidget(trl_1);
        timer_start_With_Trl(concentration_car, trl_1, scene, type_car);
        Tr_Light *trl_2 = new Tr_Light(true, 0, timer_trl);
        trl_2->setGeometry(80, 100, 100, 100);
        scene->addWidget(trl_2);
        timer_start_With_Trl(concentration_car, trl_2, scene, type_car);
        Tr_Light *trl_3 = new Tr_Light(false, 90, timer_trl);
        trl_3->setGeometry(-220, 80, 100, 150);
        scene->addWidget(trl_3);
        timer_start_With_Trl(concentration_car, trl_3, scene, type_car);
        Tr_Light *trl_4 = new Tr_Light(true, 180, timer_trl);
        trl_4->setGeometry(-140, -210, 100, 150);
        scene->addWidget(trl_4);
        timer_start_With_Trl(concentration_car, trl_4, scene, type_car);
        hide();
    }
}

/*void Start_Menu::on_pushButton_2_toggled(bool checked)
{
    circular_motion = checked;
    update();
}

void Start_Menu::on_pushButton_3_toggled(bool checked)
{
    circular_motion = checked;
    update();
}*/

void Start_Menu::on_radioButton_clicked()
{
    circular_motion = false;
    update();
}

void Start_Menu::on_radioButton_2_clicked()
{
    circular_motion = true;
    update();
}
