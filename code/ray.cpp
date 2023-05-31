#include "ray.h"
#include "cmath"
Ray::Ray(const QPointF& begin, const QPointF& end)
{
    begin_ = begin;
    end_ = end;
    double dis = sqrtf(pow(begin.x() - end.x(), 2) + pow(begin.y() - end.y(), 2));
    angle_ =  asin((abs(begin.y() - end.y())) / dis);
    if(begin.x() > end.x()){
        if(angle_ > 0){
            angle_ = M_PI - angle_;
        }else{
        angle_ = M_PI - angle_;
        }
    }
    if(end.y() > begin.y()){
        angle_ = - angle_;
    }
}

Ray::Ray(const QPointF& begin, double angle){

    begin_ = begin;
    angle_ = angle;
    double end_x;
    double end_y;
    if(angle_ > M_PI){
        angle_ = -(M_PI - (angle_  - M_PI));
    }
    if(angle_ > 0) {
        end_y = 0;
    } else if(angle_ < 0){
        end_y = 960;
    }else{
        end_y = 0;
    }



        double kat_y = abs(end_y - begin.y());
        double kat_x;
        if(angle_ <  M_PI / 2){
            kat_x = kat_y / tan(abs(angle_));
            end_x = begin.x() + kat_x;
        } else if (angle_ == M_PI / 2){
            end_x = begin.x();
        } else {
            kat_x = kat_y / tan(M_PI - abs(angle_));

            end_x = begin.x() - kat_x;
        }



    end_ = QPointF(end_x, end_y);
}
