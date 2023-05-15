#include "menu.h"
#include "ui_menu.h"
#include <QTextStream>

Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    controller(new Controller()),
        timer(new QTimer(this)),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    setFixedSize(960, 540);
    ui->gridLayout->addWidget(controller->view_);
    timer->setInterval(1000);
}

void Menu::TimerEvent(){
    controller->enemies[0]->setPosition(controller->enemies[0]->findWay(*controller->player, controller->barriers));
}

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
    controller->enemies[0]->setPosition(controller->enemies[0]->findWay(*controller->player, controller->barriers));
    controller->paint();
}
