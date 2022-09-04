#include "entities/shooter.hpp"

#include <cstdlib>  // abs

#include "entities/weapon/bullet.hpp"
#include "enums/collision-type.hpp"
#include "enums/direction.hpp"
#include "level/collidable.hpp"
#include "manager/level.hpp"

namespace entities {
    Shooter::Shooter()
        : Enemy('S'),
          shootCoolDown_(0),
          shootCoolDownMax_(20),
          logger_("Shooter") {}

    Shooter::Shooter(Position pos)
        : Enemy(pos, 3, 'S'),
          shootCoolDown_(0),
          shootCoolDownMax_(20),
          logger_("Shooter") {}

    void Shooter::resetShootCoolDown() {
        shootCoolDown_ = shootCoolDownMax_;
    }

    void Shooter::ShootCoolDown() {
        shootCoolDown_--;
        if (shootCoolDown_ < 0) {
            shootCoolDown_ = 0;
        }
    }

    bool Shooter::canShoot() {
        return shootCoolDown_ == 0;
    }

    void Shooter::attack(manager::Level *levelManager) {
        if (!canShoot()) {
            logger_.debug("Can't shoot yet");
            this->ShootCoolDown();
            return;
        }
        Position playerPosition = levelManager->getPlayer()->getPosition();
        Position currPosition = this->getPosition();
        level::Level *level = levelManager->getLevel();

        if (canAttack(levelManager)) {
            this->resetShootCoolDown();
            logger_.info("enemy firing a bullet");
            enums::Direction dir = findShootDirection(levelManager, currPosition, playerPosition);
            Position bulletPosition = Movable::_computeNextPosition(dir);
            weapon::Bullet *bullet = new weapon::Bullet(bulletPosition, dir, this->getAttack());
            level->addBullet(bullet);
        }
    }

    bool Shooter::canAttack(manager::Level *levelManager) {
        Position playerPosition = levelManager->getPlayer()->getPosition();
        Position currPosition = this->getPosition();
        level::Collidable *collision = nullptr;

        int endOffset;                 // offset della fine del check
        int xMultiplier, yMultiplier;  // modificatori della direzione
        if (currPosition.riga == playerPosition.riga) {
            xMultiplier = 0;
            yMultiplier = currPosition.colonna < playerPosition.colonna ? 1 : -1;
            endOffset = abs(currPosition.colonna - playerPosition.colonna);
        } else if (currPosition.colonna == playerPosition.colonna) {
            xMultiplier = currPosition.riga < playerPosition.riga ? 1 : -1;
            yMultiplier = 0;
            endOffset = abs(currPosition.riga - playerPosition.riga);
        } else {
            return false;
        }

        for (int i = 1; i < endOffset; i++) {
            Position checkPosition = Position(currPosition.riga + i * xMultiplier, currPosition.colonna + i * yMultiplier);
            collision = levelManager->getLevel()->getCollision(checkPosition);
            enums::CollisionType type = enums::CollisionType::NONE;
            if (collision != nullptr) type = collision->getCollisionType();
            if (type != enums::CollisionType::NONE) {
                return false;
            }
        }

        return true;
    }

    enums::Direction Shooter::findShootDirection(manager::Level *levelManager, Position currPosition, Position playerPosition) {
        if (currPosition.riga == playerPosition.riga) {
            return currPosition.colonna < playerPosition.colonna ? enums::Direction::RIGHT : enums::Direction::LEFT;
        } else if (currPosition.colonna == playerPosition.colonna) {
            return currPosition.riga < playerPosition.riga ? enums::Direction::DOWN : enums::Direction::UP;
        } else {
            return enums::Direction::NONE;
        }
    }

    void Shooter::wander(Player *player) {
        Position posPlayer = player->getPosition();
        Position posMine = this->getPosition();
        int distRiga = posPlayer.riga - posMine.riga;
        int distColonna = posPlayer.colonna - posMine.colonna;
        enums::Direction luckyestDir;
        // se è troppo vicino
        if (abs(distRiga) < 8 || abs(distColonna) < 8) {
            if (abs(distRiga) < abs(distColonna)) {
                luckyestDir = (distColonna < 0) ? enums::Direction::RIGHT : enums::Direction::LEFT;
            } else {
                luckyestDir = (distRiga > 0) ? enums::Direction::UP : enums::Direction::DOWN;
            }
        } else {
            if (abs(distRiga) > abs(distColonna)) {
                luckyestDir = (distColonna > 0) ? enums::Direction::RIGHT : enums::Direction::LEFT;
                if (distColonna == 0) luckyestDir = enums::Direction::NONE;
            } else {
                luckyestDir = (distRiga < 0) ? enums::Direction::UP : enums::Direction::DOWN;
                if (distRiga == 0) luckyestDir = enums::Direction::NONE;
            }
        }
        this->setDirection(luckyestDir);
    }
}  // namespace entities
