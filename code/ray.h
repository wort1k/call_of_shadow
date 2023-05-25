#ifndef RAY_H
#define RAY_H

#include "QPointF"
class Ray
{
private:
    QPointF begin_;
    QPointF end_;
    double angle_;
public:
    Ray(const QPointF& begin, const QPointF& end);
    Ray(const QPointF& begin, double );
    QPointF getBegin() const { return begin_; }
    QPointF getEnd() const { return end_; }
    double getAngle() { return angle_; }
    void setBegin(const QPointF& begin) {begin_ = begin; }
    void setEnd(const QPointF& end) {end_ = end; }
    void setAngle(double angle) { angle_ = angle; }
};

#endif // RAY_H
