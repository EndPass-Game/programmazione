#include <stdlib.h>
#include <mutex>

#include "direction.hpp"
#include "enemy.hpp"
#include "entity.hpp"
#include "position.hpp"

Enemy::Enemy(): 
    Entity(12, 3, // TODO: gestire queste costanti hardcoded in un file di setting
    {4, 4}, /* position di spawn */ 
    'E') {}

Enemy::Enemy(Position spawnPos): 
    Entity(12, 3,
    spawnPos,
    'E') {}

// TODO: fare vagabondare il nemico in modo più intelligente
void Enemy::wander() {
    // std::lock_guard<std::mutex> lock(mutex_); // FIXME: il mutex bugga il gioco qui
    int direction = rand() % 5;
    switch(direction) {
        case 0:
            this->setDirection(enums::Direction::UP);
            break;
        case 1:
            this->setDirection(enums::Direction::RIGHT);
            break;
        case 2:
            this->setDirection(enums::Direction::LEFT);
            break;
        case 3:
            this->setDirection(enums::Direction::DOWN);
            break;
        default:
            this->setDirection(enums::Direction::NONE);
    }
}