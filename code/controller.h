#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "vector"
#include "player.h"
#include "QGraphicsView"
#include "QGraphicsScene"
#include "QKeyEvent"
#include "barrier.h"
#include "enemy.h"
#include "QLabel"
class Controller
{
public:
    Controller();
    ~Controller();
    QLabel *hpBar;
    QGraphicsScene* scene_;
    QGraphicsView* view_;
    Player* player;
    std::vector<Barrier> barriers;
    std::vector<Enemy*> enemies;
    void fill();
    void addBarrier(Barrier);
    void paint();
    bool contact();
};

#endif // CONTROLLER_H
