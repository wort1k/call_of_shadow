#ifndef PLAYER_H
#define PLAYER_H

#include "QGraphicsScene"
#include "QPoint"
#include "QGraphicsItem"
#include "QPainter"
#include "QTextStream"
#include "QGraphicsItem"
#include "QTimer"
class Player
{
private:
    QPoint position_;
    int hieght;
    int width;
    int damage;
    int HP;

public:
    QGraphicsPixmapItem *image;
    std::vector<QPixmap> frames;
    bool wait = true;
    int currFrame = 0;
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
        pen.setWidth(5);
        scene->addLine(QLine(position_, QPoint(position_.x() + width, position_.y())), pen);
        scene->addLine(QLine(QPoint(position_.x() + width, position_.y()), QPoint(position_.x() + width, position_.y() + hieght)), pen);
        scene->addLine(QLine(QPoint(position_.x() + width, position_.y() + hieght), QPoint(position_.x(), position_.y() + hieght)), pen);
        scene->addLine(QLine(QPoint(position_.x(), position_.y() + hieght), QPoint(position_.x(), position_.y())), pen);
        image->setPos(position_);
    }
    Player()
    {
        image = new QGraphicsPixmapItem(QPixmap(":/images/Samurai1.png"));
        image->setPos(position_.x(), position_.y());
        hieght = 64;
        width = 64;
        position_ = QPoint(50, 50);
        HP = 100;
        damage = 20;
        frames = {QPixmap(":/images/Samurai1.png"), QPixmap(":/images/sprites/SamurR1.png"), QPixmap(":/images/sprites/SamurR2.png"),
                  QPixmap(":/images/sprites/SamurR3.png"), QPixmap(":/images/sprites/SamurR4.png"), QPixmap(":/images/sprites/SamurR5.png"),
                  QPixmap(":/images/sprites/SamurR6.png"), QPixmap(":/images/sprites/SamurR7.png"), QPixmap(":/images/sprites/SamurR8.png") };
    }
    void nextFrame(){
        if(!wait){
        currFrame++;
        if(currFrame == frames.size()){
            currFrame = 0;
        }
        image->setPixmap(frames[currFrame]);
        } else {
            currFrame = 0;
        }
    }
};


#endif // PLAYER_H
