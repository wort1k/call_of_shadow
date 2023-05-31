#ifndef GOPNIK_H
#define GOPNIK_H
#include "enemy.h"

class Gopnik : public Enemy
{
public:
    Gopnik();
    Gopnik(int,int);
    std::vector<QPixmap> frames;
    int currFrame = 0;
    void nextFrame();
    void paint(QGraphicsScene*) override;
    void movement(QPoint, std::vector<Barrier>, Player&) override;
    void route(std::vector<Barrier>) override;
    QPoint findWay(Player&, std::vector<Barrier>&) override;
};

#endif  GOPNIK_H
