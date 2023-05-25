#include "menu.h"
#include "ui_menu.h"
#include <QTextStream>
#include "QMessageBox"

Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    controller(new Controller()),
    timer(new QTimer(this)),
    ui(new Ui::Menu)
{
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer->start(1000 / 60);
    ui->setupUi(this);
    setFixedSize(960, 540);
    ui->gridLayout->addWidget(controller->view_);
}

void Menu::tick(){
    controller->enemies[0]->movement(controller->enemies[0]->findWay(*controller->player, controller->barriers), controller->barriers, *controller->player);
    if(controller->player->GetHP() <= 4){
        QMessageBox msgBox;
        msgBox.setText("нож в печень никто не вечен");
        msgBox.exec();
       timer->stop();

    }
    controller->paint();
}
//void Menu::timerEvent(QTimerEvent* event) {
//    controller->enemies[0]->movement(controller->enemies[0]->findWay(*controller->player, controller->barriers), controller->barriers, *controller->player);
//    if(controller->player->GetHP() <= 4){
//        QMessageBox msgBox;
//        msgBox.setText("Удар в печень никто не вечен");
//        msgBox.exec();
//       // QObject::killTimer();
//    }
//    controller->paint();
//}

Menu::~Menu()
{
    delete ui;
}

void Menu::keyPressEvent(QKeyEvent *event){
    QPoint prevPos = controller->player->getPosition();
    if(event->key() == Qt::Key_W){
        int y = controller->player->getPosition().y() - 5;
        int x = controller->player->getPosition().x();
        controller->player->setPosition(x,y);

    }else if(event->key() == Qt::Key_S){
        int y = controller->player->getPosition().y() + 5;
        int x = controller->player->getPosition().x();
        controller->player->setPosition(x,y);

    }else if(event->key() == Qt::Key_D){
        int y = controller->player->getPosition().y();
        int x = controller->player->getPosition().x()+5;
        controller->player->setPosition(x,y);
    }else if(event->key() == Qt::Key_A){
        int y = controller->player->getPosition().y();
        int x = controller->player->getPosition().x() - 5;
        controller->player->setPosition(x,y);
    }
    if(controller->contact()){
        controller->player->setPosition(prevPos);
    }
    //controller->enemies[0]->movement(controller->enemies[0]->findWay(*controller->player, controller->barriers), controller->barriers);
    //controller->paint();
}
