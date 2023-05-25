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

bool Enemy::contact(std::vector<Barrier> barriers){
    int radius = radius_;
    QPoint pos = position;
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
    return false;
}
