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
    QRectF boundingRect() const { return QRectF(position_, QPointF(position_.x()+20, position_.y() - 20)); }

public:
    int radius;
    Player();
    void setDamage(int newDamage) { damage = newDamage; }
    int getDamage() { return damage; }
    void setHP(int newHP) { HP = newHP; }
    int GetHP() { return HP; }
    void setPosition(QPoint newPos) { position_ = newPos; }
    void setPosition(int x, int y) {
        position_ = QPoint(x,y);
    }
    QPoint getPosition() { return position_; }
    void paint(QGraphicsScene*);
};


#endif // PLAYER_H
