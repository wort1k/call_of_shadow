#include "gopnik.h"
#include "QPen"

Gopnik::Gopnik(){
    position = QPoint(960 - width,540 - hieght);
    vertices_ = {QPoint(position.x() - width / 2, position.y() - hieght / 2),
                 QPoint(position.x() + width / 2, position.y() - hieght / 2),
                 QPoint(position.x() + width / 2, position.y() + hieght / 2),
                 QPoint(position.x() - width / 2, position.y() + hieght / 2)
                };
}
Gopnik::Gopnik(int x, int y)
{
    position = QPoint(x,y);
    vertices_ = {QPoint(position.x() - width / 2, position.y() - hieght / 2),
                 QPoint(position.x() + width / 2, position.y() - hieght / 2),
                 QPoint(position.x() + width / 2, position.y() + hieght / 2),
                 QPoint(position.x() - width / 2, position.y() + hieght / 2)
                };
}

void Gopnik::paint(QGraphicsScene *scene){
   QPen pen(Qt::green);
   pen.setWidth(3);
   scene->addLine(QLine(QPoint(position.x(), position.y()), QPoint(position.x() + width, position.y())), pen);
   scene->addLine(QLine(QPoint(position.x() + width, position.y()), QPoint(position.x() + width, position.y() + hieght)), pen);
   scene->addLine(QLine(QPoint(position.x() + width, position.y() + hieght), QPoint(position.x(), position.y() + hieght)), pen);
   scene->addLine(QLine(QPoint(position.x(), position.y() + hieght), QPoint(position.x(), position.y())), pen);
}

QPoint Gopnik::findWay(Player& player,std::vector<Barrier>& barriers){
    double distance = sqrt(pow(position.x() - player.getPosition().x(), 2) + pow(position.y() - player.getPosition().y(), 2));
    if( distance <= 64 * sqrt(2) + 1){

        return position;
    }
    for(int i = 1; i < barriers.size(); ++i){
        Ray ray(position, player.getPosition());
        std::optional<QPointF> a = barriers[i].IntersectRay(ray);
        if(barriers[i].IntersectRay(ray) != std::nullopt){
            return position;
        }
//        std::vector<QPoint> playerVec = {QPoint(player.getPosition().x() - width / 2, player.getPosition().y() - hieght / 2),
//                                         QPoint(player.getPosition().x() + width / 2, player.getPosition().y() - hieght / 2),
//                                         QPoint(player.getPosition().x() + width / 2, player.getPosition().y() + hieght / 2),
//                                         QPoint(player.getPosition().x() - width / 2, player.getPosition().y() + hieght / 2)
//                                        };
//        for(auto vec : vertices_) {
//            for(auto to : playerVec) {
//                if(barriers[i].IntersectRay(Ray(vec,to)) != std::nullopt){
//                    return position;
//                }
//            }
//        }

    }
    lastSeen = player.getPosition();
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

    QPoint curr = position;
    position = QPoint(position.x() + kat_x, position.y() + kat_y);
    if(contact(barriers)){
        position = curr;
        return position;
    }
    position = curr;
    return QPoint(position.x() + kat_x, position.y() + kat_y);
}


void Gopnik::movement(QPoint goTo, std::vector<Barrier> barriers, Player& player){
    if(goTo == position){
        if(sqrt(pow(position.x() - player.getPosition().x(), 2) + pow(position.y() - player.getPosition().y(), 2)) <= 64 * sqrt(2) + 1){
            if(ready == attackSpeed) {
                ready = 0;
                if(player.GetHP() < damage){
                    player.setHP(4);
                }
                player.setHP(player.GetHP() - damage);
            }
        } else if(isSearh) {
            if(searchingTime >= 5){
                route(barriers);
                isSearh = false;
                searchingTime = 0;
            } else {
                double angle = Ray(position, lastSeen).getAngle();
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
                QPoint prevPos = position;
                position = QPoint(position.x() + kat_x, position.y() + kat_y);
                if(contact(barriers)){
                    position = prevPos;
                }
                ++searchingTime;
            }
        } else {
            route(barriers);
        }
    } else {
        position = goTo;
        isSearh = true;
    }
}

void Gopnik::route(std::vector<Barrier> barriers){
    QPoint prevPos = position;
    if(facing == "left"){
        position.setX(position.x() - speed);
    }else if(facing == "right"){
        position.setX(position.x() + speed);
    }else if(facing == "up"){
        position.setY(position.y() - speed);
    }else if(facing == "down"){
        position.setY(position.y() + speed);
}
    if(contact(barriers)){
        position = prevPos;
        if(facing == "left"){
            facing = "right";
        } else if (facing == "right") {
            facing = "left";
        } else if (facing == "up") {
            facing = "down";
        } else if (facing == "down") {
            facing = "up";
        }
        if(change++ == 3){
            change = 0;
            if(facing == "left" || facing == "right"){
                facing = "up";
            } else if (facing == "up" || facing == "down") {
                facing = "left";
            }
        }
        route(barriers);
    }

}

//bool Sword::contact(std::vector<Barrier> barriers){
//    QPoint pos = position;
//    std::vector<Ray> rays ={Ray(QPoint(pos.x() - 35, pos.y() - 35), QPoint(pos.x() + 35, pos.y() - 35)),
//                           Ray(QPoint(pos.x() + 35, pos.y() - 35), QPoint(pos.x() + 35, pos.y() + 35)),
//                           Ray(QPoint(pos.x() + 35, pos.y() + 35), QPoint(pos.x() - 35, pos.y() + 35)),
//                           Ray(QPoint(pos.x() - 35, pos.y()  + 35), QPoint(pos.x() - 35, pos.y() -35)),};
//    for(auto barrier : barriers){
//        for(auto ray : rays){
//            if(barrier.IntersectRay(ray) != std::nullopt){
//                return true;
//            }
//        }
//
//    }
//    return false;
//}
