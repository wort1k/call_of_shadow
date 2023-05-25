#include "player.h"
#include "QPen"
#include "cmath"
Player::Player()
{
    hieght = 64;
    width = 64;
    radius = hieght / 2;
    position_ = QPoint(50, 50);
    HP = 100;
    damage = 20;
}

void Player::paint(QGraphicsScene* scene){
    QPen pen(Qt::red);
    pen.setWidth(3);
    scene->addLine(QLine(QPoint(position_.x() - width / 2, position_.y() - hieght / 2), QPoint(position_.x() + width / 2, position_.y() - hieght / 2)), pen);
    scene->addLine(QLine(QPoint(position_.x() + width / 2, position_.y() - hieght / 2), QPoint(position_.x() + width / 2, position_.y() + hieght / 2)), pen);
    scene->addLine(QLine(QPoint(position_.x() + width / 2, position_.y() + hieght / 2), QPoint(position_.x() - width / 2, position_.y() + hieght / 2)), pen);
    scene->addLine(QLine(QPoint(position_.x() - width / 2, position_.y() + hieght / 2), QPoint(position_.x() - width / 2, position_.y() - hieght / 2)), pen);
}
