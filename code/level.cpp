#include "level.h"

Level::Level(QPoint position, std::vector<Enemy*> enemies, std::vector<Barrier> barriers){
    position_ = position;
    enemies_ = enemies;
    barriers_ = barriers;
}
