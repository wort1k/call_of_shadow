#include "controller.h"
#include "QTextStream"
#include "QKeyEvent"
#include <algorithm>
#include "cmath"
#include "gopnik.h"
#include "ctime"
#include <fstream>
#include <sstream>
#include "QMessageBox"
Controller::Controller() :
    scene_(new QGraphicsScene()),
    view_(new QGraphicsView()),
    player(new Player()),
    hpBar(new QLabel())
{
    //hpBar->setText(QString::number(player->GetHP()));
    //hpBar->setGeometry(0,0,50,30);
    view_->setScene(scene_);
    view_->setFixedSize(960, 540);
    for(int i = 0; i < 10; ++i){
    std::vector<QPointF>points = {QPoint(i * 960, 0), QPoint(i * 960 + 960,0), QPoint(i * 960 + 960,540), QPoint(i * 960, 540)};
    barriers.push_back(Barrier(points));
    }

    levels = readLevel("C:\\Users\\User\\Desktop\\call_of_shadow-branch\\code\\input.txt");
    for(int i = 0; i < levels.size(); ++i){
    std::vector<Enemy*> en =levels[i].getEnemy();
    for(auto enemy : en){
        enemies.push_back(new Gopnik(enemy->getPos().x() + 960 * i, enemy->getPos().y()));
    }

    std::vector<Barrier> bar =levels[i].getBarrier();
    for(auto barrier : bar){
        barriers.push_back(Barrier(QPoint(barrier.GetPosition().x() + 960 * i, barrier.GetPosition().y())));
    }
    }

    for(int i = 0; i < barriers.size(); ++i){
        barriers[i].image->setOffset(barriers[i].GetPosition());
    }
    for(auto enemy : enemies) {
    enemy->image->setOffset(enemy->getPos());
    }
    player->setPosition(levels[currLevel].getPos());
    //paint();
    void newLevel(QGraphicsScene());
}

Controller::~Controller(){
    delete player;
    delete hpBar;
    delete scene_;
    delete view_;
    //enemies.clear();

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
    scene_->update();
}

void Controller::attack(){
    double min_dis = sqrt(960 *960 + 540 *540) + 10;
    int min = - 1;
    for(int i = 0; i < enemies.size(); ++i){
        double dis = sqrt(pow(enemies[i]->getPos().x() - player->getPosition().x(), 2) + pow(enemies[i]->getPos().y() - player->getPosition().y(), 2));
        if(dis <= 80*sqrt(2) && dis < min_dis){
            min_dis = dis;
            min = i;
        }
    }
    if(min != -1){
        enemies[min]->setHP(enemies[0]->getHP() - player->getDamage());
        if(enemies[min]->getHP() <= 0){
            enemies.erase(enemies.cbegin() + min - 1);
            killedEnemies++;
        }
    }

}
bool Controller::contact(){
    QPoint pos = player->getPosition();
    for(auto barrier : barriers){
        std::vector<Ray> rays ={Ray(QPoint(pos.x(), pos.y()), QPoint(pos.x() + 64, pos.y())),
                               Ray(QPoint(pos.x() + 64, pos.y()), QPoint(pos.x() + 64, pos.y() + 64)),
                               Ray(QPoint(pos.x() + 64, pos.y() + 64), QPoint(pos.x(), pos.y() + 64)),
                               Ray(QPoint(pos.x(), pos.y()  + 64), QPoint(pos.x(), pos.y()))};
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


std::vector<Level> Controller::readLevel(std::string filename){
    std::ifstream file;
    std::vector<Level> result;
    file.open(filename);
    if(!file.is_open()){
        QMessageBox msgBox;
        msgBox.setText("нож в печень никто не вечен");
        msgBox.exec();
    }else {
    std::string temp;
    std::getline(file, temp);
    int num = std::stoi(temp);
    for(int i = 0; i < num; ++i){
        int x, y;
        std::getline(file, temp, ' ');
        x = std::stoi(temp);
        std::getline(file, temp);
        y = std::stoi(temp);
        std::getline(file, temp, ' ');
        int enemyCount = std::stoi(temp);
        std::vector<Enemy*> levelEnemy;
        for(int j = 0; j < enemyCount - 1; ++j){
            std::getline(file, temp, ' ');
            int enemyX = std::stoi(temp);
            std::getline(file, temp, ' ');
            int enemyY = std::stoi(temp);
            Enemy* gop = new Gopnik(enemyX, enemyY);
            levelEnemy.push_back(gop);
        }
        std::getline(file, temp, ' ');
        int enemyX = std::stoi(temp);
        std::getline(file, temp);
        int enemyY = std::stoi(temp);
        Enemy* gop = new Gopnik(enemyX, enemyY);
        levelEnemy.push_back(gop);
        std::getline(file, temp, ' ');
        int barrierCount = std::stoi(temp);
        std::vector<Barrier> levelBarrier;
        for(int j = 0; j < barrierCount - 1; ++j){
            std::getline(file, temp, ' ');
            int barrierX = std::stoi(temp);
            std::getline(file, temp, ' ');
            int barrierY = std::stoi(temp);
            levelBarrier.push_back(Barrier(QPoint(barrierX, barrierY)));
        }
        std::getline(file, temp, ' ');
        int barrierX = std::stoi(temp);
        std::getline(file, temp);
        int barrierY = std::stoi(temp);
        levelBarrier.push_back(Barrier(QPoint(barrierX, barrierY)));
        result.push_back(Level(QPoint(x,y), levelEnemy, levelBarrier));
    }
}
    file.close();
    return result;
}

