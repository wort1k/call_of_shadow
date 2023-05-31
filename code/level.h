#ifndef LEVEL_H
#define LEVEL_H
#include "enemy.h"
#include "barrier.h"
#include <vector>
class Level
{
private:
    QPoint position_;
    std::vector<Barrier> barriers_;
    std::vector<Enemy*> enemies_;
public:
    Level(QPoint, std::vector<Enemy*>, std::vector<Barrier>);
    QPoint getPos() { return position_; }
    std::vector<Enemy*> getEnemy() { return enemies_; }
    std::vector<Barrier> getBarrier() {return barriers_; }
};

#endif // LEVEL_H
