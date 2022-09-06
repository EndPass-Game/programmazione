#include "entities/kamikaze.hpp"

#include <cstdlib>  // abs

#include "manager/level.hpp"

namespace entities {
    Kamikaze::Kamikaze(Position pos)
        : Enemy(pos, 7, 'K') {}

    void Kamikaze::attack(manager::Level *levelManager) {
        if (canAttack(levelManager)) {
            this->attackEntity(levelManager->getPlayer());
            this->life_ = 0;  // marchiamo come morto
            levelManager->getLogQueue()->addEvent("Il nemico e' esploso");
            // levelManager->getLevel()->deleteCollidable((level::Collidable *) this);
        }
    }

    void Kamikaze::wander(Player *player) {
        Position posPlayer = player->getPosition();
        Position posMine = this->getPosition();
        int distRiga = posPlayer.riga - posMine.riga;
        int distColonna = posPlayer.colonna - posMine.colonna;
        enums::Direction luckyestDir;
        if (abs(distRiga) < abs(distColonna)) {
            luckyestDir = (distColonna > 0) ? enums::Direction::RIGHT : enums::Direction::LEFT;
        } else {
            luckyestDir = (distRiga < 0) ? enums::Direction::UP : enums::Direction::DOWN;
        }
        this->setDirection(luckyestDir);
    }

    bool Kamikaze::canAttack(manager::Level *levelManager) {
        Position playerPosition = levelManager->getPlayer()->getPosition();
        Position currPosition = this->getPosition();
        return abs(playerPosition.riga - currPosition.riga) <= 1 && abs(playerPosition.colonna - currPosition.colonna) <= 1;
    }
}  // namespace entities