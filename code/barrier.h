#ifndef BARRIER_H
#define BARRIER_H


#include <vector>
#include <optional>
#include "QPointF"
#include "ray.h"
#include "QGraphicsScene"
#include "QDebug"
#include "QGraphicsItem"
class Barrier
{
private:
    std::vector<QPointF> vertices_;
    QPoint position;
public:
    QGraphicsPixmapItem* image = new QGraphicsPixmapItem(QPixmap(":/images/sprites/Kust64.png"));
    Barrier();
    Barrier(const std::vector<QPointF>& vertices) { vertices_ = vertices;
                                                    image->setPixmap(QPixmap(":/images/sprites/trava.png"));
                                                    position = QPoint(vertices[0].x(), vertices[0].y()); }
    Barrier(QPoint);
    std::vector<QPointF> getVertices() {return vertices_; }
    std::optional<QPointF> IntersectRay(const Ray& ray);
    QPoint GetPosition(){return position; }
    void paint(QGraphicsScene*);

};
#endif // BARRIER_H
