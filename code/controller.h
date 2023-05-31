#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include "vector"
#include "player.h"
#include "QGraphicsView"
#include "QGraphicsScene"
#include "QKeyEvent"
#include "barrier.h"
#include "enemy.h"
#include "QLabel"
#include "level.h"
class Controller{
signals:
    void newLevel(){}
public:
    int currLevel = 0;
    Controller();
    ~Controller();
    QLabel *hpBar;
    QGraphicsScene* scene_;
    QGraphicsView* view_;
    Player* player;
    std::vector<Level> levels;
    std::vector<Barrier> barriers;
    std::vector<Enemy*> enemies;
    void addBarrier(Barrier);
    void paint();
    void attack();
    std::vector<Level> readLevel(std::string);
    bool contact();
    QGraphicsPixmapItem* image;
    int killedEnemies = 0;
};

#endif // CONTROLLER_H
