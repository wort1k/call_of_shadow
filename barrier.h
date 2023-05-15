#ifndef BARRIER_H
#define BARRIER_H


#include <vector>
#include <optional>
#include "QPointF"
#include "ray.h"
#include "QGraphicsScene"
#include "QDebug"
class Barrier
{
private:
    std::vector<QPointF> vertices_;
    QPoint position;
public:
    Barrier(const std::vector<QPointF>& vertices) { vertices_ = vertices; }
    Barrier(QPoint);
    std::vector<QPointF> getVertices() {return vertices_; }
    std::optional<QPointF> IntersectRay(const Ray& ray);
    QPoint GetPosition(){return position; }
    void paint(QGraphicsScene*);

};
#endif // BARRIER_H
