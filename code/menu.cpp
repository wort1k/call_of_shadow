#include "menu.h"
#include "ui_menu.h"
#include <QTextStream>
#include "QMessageBox"

Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    controller(new Controller()),
    timer(new QTimer(this)),
    wait(new QTimer(this)),
    ui(new Ui::Menu)
{
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    connect(wait, SIGNAL(timeout()), this, SLOT(nothing()));
    //connect(controller, SIGNAL(controller->newLevel()), this, SLOT(newLevel()));
    timer->start(1000 / 60);
    ui->setupUi(this);
    setFixedSize(960, 540);
    //view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_ = new QGraphicsView();
    scene_ = new QGraphicsScene();
    view_->setScene(scene_);
    ui->gridLayout->addWidget(view_);
    for(int i = 0; i < controller->barriers.size(); ++i){
        scene_->addItem(controller->barriers[i].image);
    }
    scene_->addItem(controller->player->image);
    //view_->setSceneRect(QRectF(QPoint(960,0), QPoint(960,540)));
    paint();
}

void Menu::tick(){
    for(int i = 0; i < controller->enemies.size(); ++i){
        if(controller->enemies[i]->ready < controller->enemies[i]->attackSpeed){
            controller->enemies[i]->ready++;
        }
    controller->enemies[i]->movement(controller->enemies[i]->findWay(*controller->player, controller->barriers), controller->barriers, *controller->player);
    }
    if(controller->player->GetHP() <= 4){
        QMessageBox msgBox;
        msgBox.setText("нож в печень никто не вечен");
        msgBox.exec();
       timer->stop();

    }
    for(int i = 0; i < controller->enemies.size(); ++i){
    controller->enemies[i]->image->setOffset(controller->enemies[i]->getPos());
    }
    //for(int i = 0; i < controller->enemies.size(); ++i){
    //    if(controller->enemies[i]->getHP() <= 0){
    //        controller->enemies.erase(controller->enemies.begin() + i - 1);
    //        controller->enemyItem.erase(controller->enemyItem.begin() + i - 1);
    //    }
    //}
    if(controller->killedEnemies == controller->levels[controller->currLevel].getEnemy().size()){
        controller->killedEnemies = 0;
        controller->currLevel++;
        if(controller->currLevel == controller->levels.size()){
            scene_->clear();
            QMessageBox msgBox;
            msgBox.setText("вы прошли игру");
            msgBox.exec();
        } else {
            view_->setSceneRect(QRectF(QPoint(controller->currLevel * 960, 0),QPoint(QPoint(controller->currLevel * 960 + 960, 540))));
            controller->player->setPosition(QPoint(controller->levels[controller->currLevel].getPos().x() + 960 * controller->currLevel, controller->levels[controller->currLevel].getPos().y()));
        }
    }
    update();
    //controller->player->paint(scene_);
    //controller->enemies.back()->paint(scene_);
    scene_->update();
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
    }else if (event->key() == Qt::Key_Space) {
        controller->attack();
}
    if(controller->contact()){
        controller->player->setPosition(prevPos);
    }
    controller->player->wait = false;
    wait->stop();
    wait->start(100);
    //controller->enemies[0]->movement(controller->enemies[0]->findWay(*controller->player, controller->barriers), controller->barriers);
    controller->paint();
}

void Menu::paint(){
    for(int i = 0; i < controller->enemies.size(); ++i){
        scene_->addItem(controller->enemies[i]->image);
    }
}

void Menu::update(){
    controller->player->nextFrame();
}

void Menu::newLevel(){
    scene_->removeItem(controller->player->image);
}
