#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "vector"
#include "player.h"
#include "QGraphicsView"
#include "QGraphicsScene"
#include "QKeyEvent"
#include "barrier.h"
#include "enemy.h"

class Controller
{
public:
    Controller();
    QGraphicsScene* scene_;
    QGraphicsView* view_;
    Player* player;
    std::vector<Barrier> barriers;
    std::vector<Enemy*> enemies;
    std::vector<std::vector<int>> field;
    void addBarrier(Barrier);
    void paint();
    bool contact();
};

#endif // CONTROLLER_H
