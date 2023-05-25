#include "controller.h"
#include "QTextStream"
#include "QKeyEvent"
#include <algorithm>
#include "cmath"
#include "gopnik.h"
#include "ctime"

Controller::Controller() :
    scene_(new QGraphicsScene()),
    view_(new QGraphicsView()),
    player(new Player()),
    hpBar(new QLabel())
{
    hpBar->setText(QString::number(player->GetHP()));
    hpBar->setGeometry(0,0,50,30);
    view_->setScene(scene_);
    view_->setFixedSize(960, 540);
    std::vector<QPointF>points = {QPoint(0,0), QPoint(960,0), QPoint(960,540), QPoint(0,540)};
    barriers.push_back(Barrier(points));
    fill();
    Sword *sw = new Sword();
    enemies.push_back(sw);
    paint();
    scene_->addWidget(hpBar);

}

Controller::~Controller(){
    delete player;
    delete hpBar;
    delete scene_;
    delete view_;
    enemies.clear();

}
void Controller::addBarrier(Barrier barrier){
    barriers.push_back(barrier);
}

void Controller::paint(){
    scene_->clear();
    QPen pen(Qt::red);
    pen.setWidth(1);
    QBrush brush(Qt::red);
    player->paint(scene_);
    for(auto barrier : barriers){
        barrier.paint(scene_);
    }
    for(auto enemy : enemies){
      enemy->paint(scene_);
    }
    scene_->addRect(QRect(3, 3, player->GetHP() * 2, 30), pen, brush);
}

bool Controller::contact(){
    int radius = player->radius;
    QPoint pos = player->getPosition();
    for(auto barrier : barriers){
        std::vector<Ray> rays ={Ray(QPoint(pos.x() - 35, pos.y() - 35), QPoint(pos.x() + 35, pos.y() - 35)),
                               Ray(QPoint(pos.x() + 35, pos.y() - 35), QPoint(pos.x() + 35, pos.y() + 35)),
                               Ray(QPoint(pos.x() + 35, pos.y() + 35), QPoint(pos.x() - 35, pos.y() + 35)),
                               Ray(QPoint(pos.x() - 35, pos.y()  + 35), QPoint(pos.x() - 35, pos.y() -35)),};
        for(auto barrier : barriers){
            for(auto ray : rays){
                if(barrier.IntersectRay(ray) != std::nullopt){
                    return true;
                }
            }

        }
        }
    return false;
}

void Controller::fill(){
    srand(time(0));
    //int number = rand() % 20 + 1;
    QPoint first(100, 100);
    barriers.push_back(Barrier(first));
    first = QPoint(164, 164);
    barriers.push_back(Barrier(first));
    first = QPoint(300, 300);
    barriers.push_back(Barrier(first));
    //first = QPoint(rand() % 860 + 65, rand() % 440 + 65);
    //    barriers.push_back(Barrier(first));
    //for(int i = 0; i <number; ++i){
    //    first = QPoint(rand() % 860 + 65, rand() % 440 + 65);
    //    barriers.push_back(Barrier(first));
    //}
    //
    //
}
