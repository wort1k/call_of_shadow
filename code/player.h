#ifndef PLAYER_H
#define PLAYER_H

#include "QGraphicsScene"
#include "QPoint"
#include "QGraphicsItem"
#include "QPainter"
#include "QTextStream"
class Player
{
private:
    QPoint position_;
    int hieght;
    int width;
    int damage;
    int HP;

public:
    int radius;
    void setDamage(int newDamage) { damage = newDamage; }
    int getDamage() { return damage; }
    void setHP(int newHP) { HP = newHP; }
    int GetHP() { return HP; }
    void setPosition(QPoint newPos) { position_ = newPos; }
    void setPosition(int x, int y) {
        position_ = QPoint(x,y);
    }
    QPoint getPosition() { return position_; }
    void paint(QGraphicsScene* scene){
        QPen pen(Qt::red);
        pen.setWidth(3);
        scene->addLine(QLine(QPoint(position_.x() - width / 2, position_.y() - hieght / 2), QPoint(position_.x() + width / 2, position_.y() - hieght / 2)), pen);
        scene->addLine(QLine(QPoint(position_.x() + width / 2, position_.y() - hieght / 2), QPoint(position_.x() + width / 2, position_.y() + hieght / 2)), pen);
        scene->addLine(QLine(QPoint(position_.x() + width / 2, position_.y() + hieght / 2), QPoint(position_.x() - width / 2, position_.y() + hieght / 2)), pen);
        scene->addLine(QLine(QPoint(position_.x() - width / 2, position_.y() + hieght / 2), QPoint(position_.x() - width / 2, position_.y() - hieght / 2)), pen);
    }
    Player()
    {
        hieght = 64;
        width = 64;
        radius = hieght / 2;
        position_ = QPoint(50, 50);
        HP = 100;
        damage = 20;
    }
};


#endif // PLAYER_H
