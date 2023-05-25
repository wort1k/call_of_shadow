#include "barrier.h"
#include "cmath"
#include "QPen"

Barrier::Barrier(QPoint pos){
    position = pos;
    vertices_ = {pos, QPoint(pos.x() + 64,pos.y()), QPoint(pos.x()+64,pos.y()+64), QPoint(pos.x(),pos.y()+64)};
}

std::optional<QPointF> Barrier::IntersectRay(const Ray& ray){

    std::vector<QPointF> intesectSuspect;
    QPointF begin = ray.getBegin();
    QPointF end = ray.getEnd();
    QPointF vec_ray(end.x() - begin.x(), end.y() - begin.y());
    for(uint64_t i = 0; i < vertices_.size() - 1; ++i){

        QPointF vec_1(vertices_[i].x() - begin.x(), vertices_[i].y() - begin.y());
        QPointF vec_2(vertices_[i+1].x() - begin.x(), vertices_[i+1].y() - begin.y());
        double mul_1 = vec_ray.x() * vec_1.y() - vec_ray.y() * vec_1.x();
        double mul_2 = vec_ray.x() * vec_2.y() - vec_ray.y() * vec_2.x();
        if((mul_1 < 0 && mul_2 > 0) ||( mul_1 > 0 && mul_2 < 0)){
            QPointF vec_side(vertices_[i+1].x() - vertices_[i].x(), vertices_[i+1].y() - vertices_[i].y());
            QPointF vec_3(begin.x() - vertices_[i].x() , begin.y() - vertices_[i].y());
            QPointF vec_4(end.x() - vertices_[i].x(), end.y() - vertices_[i].y());
            double mul_3 = vec_side.x() * vec_3.y() - vec_side.y() * vec_3.x();
            double mul_4 = vec_side.x() * vec_4.y() - vec_side.y() * vec_4.x();
            if((mul_3 < 0 && mul_4 > 0) ||( mul_3 > 0 && mul_4 < 0)){
                double x = vertices_[i].x() + (vertices_[i+1].x() - vertices_[i].x())*abs(mul_1)/abs(mul_2 - mul_1);
                double y = vertices_[i].y() + (vertices_[i+1].y() - vertices_[i].y())*abs(mul_1)/abs(mul_2 - mul_1);
                intesectSuspect.push_back(QPointF(x,y));
            }
        }
    }
    QPointF vec_1(vertices_.back().x() - begin.x(), vertices_.back().y() - begin.y());
    QPointF vec_2(vertices_[0].x() - begin.x(), vertices_[0].y() - begin.y());
    double mul_1 = vec_ray.x() * vec_1.y() - vec_ray.y() * vec_1.x();
    double mul_2 = vec_ray.x() * vec_2.y() - vec_ray.y() * vec_2.x();
    if((mul_1 < 0 && mul_2 > 0) ||( mul_1 > 0 && mul_2 < 0)){
        QPointF vec_side(vertices_[0].x() - vertices_.back().x(), vertices_[0].y() - vertices_.back().y());
        QPointF vec_3(begin.x() - vertices_.back().x() , begin.y() - vertices_.back().y());
        QPointF vec_4(end.x() - vertices_.back().x(), end.y() - vertices_.back().y());
        double mul_3 = vec_side.x() * vec_3.y() - vec_side.y() * vec_3.x();
        double mul_4 = vec_side.x() * vec_4.y() - vec_side.y() * vec_4.x();
        if((mul_3 < 0 && mul_4 > 0) ||( mul_3 > 0 && mul_4 < 0)){
            double x = vertices_.back().x() + (vertices_[0].x() - vertices_.back().x())*abs(mul_1)/abs(mul_2 - mul_1);
            double y = vertices_.back().y() + (vertices_[0].y() - vertices_.back().y())*abs(mul_1)/abs(mul_2 - mul_1);
            intesectSuspect.push_back(QPointF(x,y));
        }
    }

        if(intesectSuspect.empty()){
            return std::nullopt;
        }
        double min_dis = sqrtf(pow(begin.x() - intesectSuspect[0].x(), 2) + pow(begin.y() - intesectSuspect[0].y(), 2));
        uint64_t min = 0;
        for(uint64_t i = 1; i < intesectSuspect.size(); ++i){
            double dis = sqrtf(pow(begin.x() - intesectSuspect[i].x(), 2) + pow(begin.y() - intesectSuspect[i].y(), 2));
            if(dis < min_dis){
                min_dis = dis;
                min = i;
            }
        }

return intesectSuspect[min];
}

void Barrier::paint(QGraphicsScene *scene){
        QPen pen(Qt::black);
        pen.setWidth(3);
    for(uint64_t i = 0; i < vertices_.size() - 1; ++i){
        scene->addLine(QLineF(vertices_[i], vertices_[i+1]),  pen);
    }
    scene->addLine(QLineF(vertices_.back(), vertices_[0]),  pen);
}





