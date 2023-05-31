#include "enemy.h"
#include <cmath>
Enemy::Enemy(){
    position = QPoint(960 - width,540 - hieght);
    vertices_ = {QPoint(position.x(), position.y()),
                 QPoint(position.x() + width, position.y()),
                 QPoint(position.x() + width, position.y() + hieght),
                 QPoint(position.x(), position.y() + hieght)
                };
}
Enemy::Enemy(int x, int y)
{
    position = QPoint(x,y);
    vertices_ = {QPoint(position.x(), position.y()),
                 QPoint(position.x() + width, position.y()),
                 QPoint(position.x() + width, position.y() + hieght),
                 QPoint(position.x(), position.y() + hieght)
                };
}

bool Enemy::contact(std::vector<Barrier> barriers){
    int radius = radius_;
    QPoint pos = position;
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
    return false;
}
