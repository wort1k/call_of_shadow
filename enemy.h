#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "QPoint"
#include "QGraphicsScene"
#include "barrier.h"
#include "ray.h"
#include "player.h"
class Enemy
{
protected:
    QPoint position;
    std::vector<QPoint> vertices_;
    int hp = 50;
    int damage = 5;
    int speed = 5;
    bool isSearh = false;
    bool onRoute = true;
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
    void paint(QGraphicsScene*);
    void movement();
    QPoint findWay(Player&, std::vector<Barrier>&);

};

#endif // ENEMY_H
