#include "controller.h"
#include "QTextStream"
#include "QKeyEvent"
#include <algorithm>
#include "cmath"
#include "sword.h"

Controller::Controller() :
    scene_(new QGraphicsScene()),
    view_(new QGraphicsView()),
    player(new Player())
{
    view_->setScene(scene_);
    view_->setFixedSize(960, 540);
    std::vector<QPointF>points = {QPoint(0,0), QPoint(960,0), QPoint(960,540), QPoint(0,540)};
    field = std::vector<std::vector<int>>(540,std::vector<int>(960, 0));
    barriers.push_back(Barrier(points));
    addBarrier(Barrier(QPoint(100,100)));
    Enemy *sw = new Enemy(300,50);
    enemies.push_back(sw);
    enemies[0]->findWay(*player, barriers);
    paint();

}

void Controller::addBarrier(Barrier barrier){
    barriers.push_back(barrier);
    if(barrier.GetPosition().x() % 10 != 0){
        if(barrier.GetPosition().y() % 10 != 0){
            field[barrier.GetPosition().y() - barrier.GetPosition().y() % 10][barrier.GetPosition().x() - barrier.GetPosition().x() % 10] = -1;
            field[barrier.GetPosition().y() - barrier.GetPosition().y() % 10][barrier.GetPosition().x() - barrier.GetPosition().x() % 10 + 10] = -1;
            field[barrier.GetPosition().y() - barrier.GetPosition().y() % 10 + 10][barrier.GetPosition().x() - barrier.GetPosition().x() % 10 + 10] = -1;
            field[barrier.GetPosition().y() - barrier.GetPosition().y() % 10 + 10][barrier.GetPosition().x() - barrier.GetPosition().x() % 10] = -1;
        }else{
            field[barrier.GetPosition().y()][barrier.GetPosition().x() - barrier.GetPosition().x() % 10] = -1;
            field[barrier.GetPosition().y()][barrier.GetPosition().x() - barrier.GetPosition().x() % 10 + 10] = -1;
        }
    }else{
        if(barrier.GetPosition().y() % 10 != 0){
            field[barrier.GetPosition().y() - barrier.GetPosition().y() % 10][barrier.GetPosition().x()] = -1;
            field[barrier.GetPosition().y() - barrier.GetPosition().y() % 10 + 10][barrier.GetPosition().x()] = -1;
        }
    }
}

void Controller::paint(){
    scene_->clear();
    QPen pen(Qt::black);
    pen.setWidth(3);
    player->paint(scene_);
    for(auto barrier : barriers){
        barrier.paint(scene_);
    }
    for(auto enemy : enemies){
      enemy->paint(scene_);
    }
}

bool Controller::contact(){
    int radius = player->radius;
    QPoint pos = player->getPosition();
    for(auto barrier : barriers){
        for(uint64_t i = 0; i < barrier.getVertices().size() - 1; ++i) {
            QPointF vec_1(barrier.getVertices()[i+1].x() - barrier.getVertices()[i].x(), barrier.getVertices()[i+1].y() - barrier.getVertices()[i].y());
            QPointF vec_2(-vec_1.x(), - vec_1.y());
            QPointF vec( -barrier.getVertices()[i].x() + pos.x(), - barrier.getVertices()[i].y() + pos.y());
            QPointF vec2( - barrier.getVertices()[i+1].x() + pos.x(), - barrier.getVertices()[i+1].y() + pos.y());
            if(vec_1.x() * vec.x() + vec_1.y() * vec.y() <= 0) {
                double distance = sqrt(pow(pos.x() - barrier.getVertices()[i].x(), 2) + pow(pos.y() - barrier.getVertices()[i].y(), 2));
                if (distance <= radius){
                    return true;
                }
            } else if (vec_2.x() * vec2.x() + vec_2.y() * vec2.y() <= 0) {
                double distance = sqrt(pow(pos.x() - barrier.getVertices()[i+1].x(), 2) + pow(pos.y() - barrier.getVertices()[i+1].y(), 2));
                if (distance < radius){
                    return true;
                }
            } else {
                double x,y;
                if(barrier.getVertices()[i+1].x() == barrier.getVertices()[i].x()){
                    x = barrier.getVertices()[i].x();
                    y = pos.y();
                }else if(barrier.getVertices()[i+1].y() == barrier.getVertices()[i].y()){
                    y = barrier.getVertices()[i].y();
                    x = pos.x();
                }else{
                    double a = barrier.getVertices()[i+1].x() - barrier.getVertices()[i].x();
                    double b = barrier.getVertices()[i+1].y() - barrier.getVertices()[i].y();
                    y = ((a * a / b) * barrier.getVertices()[i].y() + a * (pos.x() - barrier.getVertices()[i].x())+ b * pos.y())/ (a * a / b + b);
                    x = a / (y - barrier.getVertices()[i].y()) + barrier.getVertices()[i].x();

                }
                double distance = sqrt(pow((x-pos.x()),2) + pow((y-pos.y()),2));
                if(distance < radius){
                    return true;
                }
            }
        }


        QPointF vec_1(barrier.getVertices()[0].x() - barrier.getVertices().back().x(), barrier.getVertices()[0].y() - barrier.getVertices().back().y());
        QPointF vec_2(-vec_1.x(), - vec_1.y());
        QPointF vec( -barrier.getVertices().back().x() + pos.x(), - barrier.getVertices().back().y() + pos.y());
        QPointF vec2( - barrier.getVertices()[0].x() + pos.x(), - barrier.getVertices()[0].y() + pos.y());
        if(vec_1.x() * vec.x() + vec_1.y() * vec.y() <= 0) {
            double distance = sqrt(pow(pos.x() - barrier.getVertices().back().x(), 2) + pow(pos.y() - barrier.getVertices().back().y(), 2));
            if (distance <= radius){
                return true;
            }
        } else if (vec_2.x() * vec2.x() + vec_2.y() * vec2.y() <= 0) {
            double distance = sqrt(pow(pos.x() - barrier.getVertices()[0].x(), 2) + pow(pos.y() - barrier.getVertices()[0].y(), 2));
            if (distance < radius){
                return true;
            }
        } else {
            double x,y;
            if(barrier.getVertices()[0].x() == barrier.getVertices().back().x()){
                x = barrier.getVertices().back().x();
                y = pos.y();
            }else if(barrier.getVertices()[0].y() == barrier.getVertices().back().y()){
                y = barrier.getVertices().back().y();
                x = pos.x();
            }else{
                double a = barrier.getVertices()[0].x() - barrier.getVertices().back().x();
                double b = barrier.getVertices()[0].y() - barrier.getVertices().back().y();
                y = ((a * a / b) * barrier.getVertices().back().y() + a * (pos.x() - barrier.getVertices().back().x())+ b * pos.y())/ (a * a / b + b);
                x = a / (y - barrier.getVertices().back().y()) + barrier.getVertices().back().x();

            }
            double distance = sqrt(pow((x-pos.x()),2) + pow((y-pos.y()),2));
            if(distance < radius){
                return true;
            }
        }
    }
    return false;
}



//при создании припятсвия изменять филд
