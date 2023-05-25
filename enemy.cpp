#include "enemy.h"
#include <cmath>
Enemy::Enemy(){
    position = QPoint(960 - width,540 - hieght);
    vertices_ = {QPoint(position.x() - width / 2, position.y() - hieght / 2),
                 QPoint(position.x() + width / 2, position.y() - hieght / 2),
                 QPoint(position.x() + width / 2, position.y() + hieght / 2),
                 QPoint(position.x() - width / 2, position.y() + hieght / 2)
                };
}
Enemy::Enemy(int x, int y)
{
    position = QPoint(x,y);
    vertices_ = {QPoint(position.x() - width / 2, position.y() - hieght / 2),
                 QPoint(position.x() + width / 2, position.y() - hieght / 2),
                 QPoint(position.x() + width / 2, position.y() + hieght / 2),
                 QPoint(position.x() - width / 2, position.y() + hieght / 2)
                };
}

void Enemy::paint(QGraphicsScene *scene){
    QPen pen(Qt::green);
    pen.setWidth(3);
    scene->addLine(QLine(QPoint(position.x() - width / 2, position.y() - hieght / 2), QPoint(position.x() + width / 2, position.y() - hieght / 2)), pen);
    scene->addLine(QLine(QPoint(position.x() + width / 2, position.y() - hieght / 2), QPoint(position.x() + width / 2, position.y() + hieght / 2)), pen);
    scene->addLine(QLine(QPoint(position.x() + width / 2, position.y() + hieght / 2), QPoint(position.x() - width / 2, position.y() + hieght / 2)), pen);
    scene->addLine(QLine(QPoint(position.x() - width / 2, position.y() + hieght / 2), QPoint(position.x() - width / 2, position.y() - hieght / 2)), pen);
}

QPoint Enemy::findWay(Player& player,std::vector<Barrier>& barriers){
    for(int i = 1; i < barriers.size(); ++i){
        if(barriers[i].IntersectRay(Ray(position, player.getPosition())) != std::nullopt){
            return position;
        }
        std::vector<QPoint> playerVec = {QPoint(player.getPosition().x() - width / 2, player.getPosition().y() - hieght / 2),
                                         QPoint(player.getPosition().x() + width / 2, player.getPosition().y() - hieght / 2),
                                         QPoint(player.getPosition().x() + width / 2, player.getPosition().y() + hieght / 2),
                                         QPoint(player.getPosition().x() - width / 2, player.getPosition().y() + hieght / 2)
                                        };
        for(auto vec : vertices_) {
            for(auto to : playerVec) {
                if(barriers[i].IntersectRay(Ray(vec,to)) != std::nullopt){
                    return position;
                }
            }
        }

    }

    double angle = Ray(position, player.getPosition()).getAngle();
    double kat_x;
    double kat_y;
    if(abs(angle) <= M_PI / 2){
        kat_x = cos(abs(angle)) * speed;
        kat_y = sin(abs(angle)) * speed;
    } else {
        kat_x = - cos(M_PI - abs(angle)) * speed;
        kat_y = sin(M_PI - abs(angle)) * speed;
    }
    if(angle > 0){
       kat_y *= -1;
    }

    return QPoint(position.x() + kat_x, position.y() + kat_y);
}
