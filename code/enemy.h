#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <cmath>
#include "QPoint"
#include "QGraphicsScene"
#include "barrier.h"
#include "ray.h"
#include "player.h"
class Enemy
{
public:
    int attackSpeed = 10;
    int ready = attackSpeed;
    QGraphicsPixmapItem* image = new QGraphicsPixmapItem(QPixmap(":/images/sprites/Gopn.png"));
protected:
    QPoint position;
    int radius_ = 32;
    std::vector<QPoint> vertices_;
    int hp = 3;
    int damage = 0;
    int speed = 3;
    bool isSearh = false;
    int searchingTime = 0;
    QPoint lastSeen;
    std::string facing = "left";
    int change = 0;
public:
    int hieght = 64;
    int width = 64;
    Enemy();
    Enemy(int,int);
    void setHP(int newHP) { hp = newHP; }
    void setDamage(int newDamage) { damage = newDamage; }
    void setPosition(QPoint newPos){ position = newPos; }
    int getHP() { return hp; }
    int getDamage() {return damage; }
    QPoint getPos() {return position; }
    virtual void paint(QGraphicsScene*){}
    virtual void movement(QPoint, std::vector<Barrier>, Player&){}
    virtual void route(std::vector<Barrier>){}
    bool contact(std::vector<Barrier>);
    virtual QPoint findWay(Player&, std::vector<Barrier>&){}

};

#endif // ENEMY_H
