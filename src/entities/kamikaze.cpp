#include "entities/kamikaze.hpp"

#include <cstdlib>  // abs

#include "manager/level.hpp"
namespace entities {
    Kamikaze::Kamikaze()
        : Enemy('K') {}

    Kamikaze::Kamikaze(Position pos)
        : Enemy(pos, 7, 'K') {}

    void Kamikaze::attack(manager::Level *levelManager) {
        if (canAttack(levelManager)) {
            this->attackEntity(levelManager->getPlayer());
            levelManager->getLogQueue()->addEvent("Il nemico e' esploso");
            levelManager->getLevel()->deleteCollidable((level::Collidable *) this);
        }
    }

    bool Kamikaze::canAttack(manager::Level *levelManager) {
        Position playerPosition = levelManager->getPlayer()->getPosition();
        Position currPosition = this->getPosition();
        return abs(playerPosition.riga - currPosition.riga) <= 1 && abs(playerPosition.colonna - currPosition.colonna) <= 1;
    }

}  // namespace entities