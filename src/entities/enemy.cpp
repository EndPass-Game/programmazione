#include "entities/enemy.hpp"

#include <mutex>
#include <stdlib.h>

#include "entities/entity.hpp"
#include "enums/collision-type.hpp"
#include "enums/direction.hpp"
#include "level/collidable.hpp"
#include "manager/level.hpp"
namespace entities {
    Enemy::Enemy()
        : Entity(12, 5,  // TODO: gestire queste costanti hardcoded in un file di setting
                 {4, 4}, /* position di spawn */
                 'E'),
          logger_("Enemy") {}

    Enemy::Enemy(Position spawnPos)
        : Entity(12, 5, spawnPos, 'E'),
          coolDown_(0),
          coolDownMax_(10),  // può muoversi ogni 10 frame
          logger_("Enemy") {}
    // TODO: fare vagabondare il nemico in modo più intelligente
    void Enemy::wander() {
        // std::lock_guard<std::mutex> lock(mutex_); // FIXME: il mutex bugga il gioco qui
        int direction = rand() % 5;
        switch (direction) {
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
    // probabilmente inutile visto che andrebbe automaticamente a prendere quella di displayable (?)
    void Enemy::setPosition(Position pos) {
        Displayable::setPosition(pos);
    }
    void Enemy::_handleDoorCollision(manager::Level *levelManager, level::DoorSegment *door) {
    }
    void Enemy::_handleWallCollision(manager::Level *levelManager, level::WallSegment *wall) {
    }
    void Enemy::_handleEntityCollision(manager::Level *levelManager, Entity *entity) {
    }
    void Enemy::_handleArtifactCollision(manager::Level *levelManager, collectables::Artifact *artifact) {
    }
    void Enemy::_handlePowerCollision(manager::Level *levelManager, collectables::Power *power) {
    }
    void Enemy::_handleNoneCollision(manager::Level *levelManager) {
        this->setPosition(nextPosition_);
    }

    void Enemy::resetCoolDown() {
        coolDown_ = coolDownMax_;
    }

    void Enemy::moveCoolDown() {
        coolDown_--;
        if (coolDown_ < 0) {
            coolDown_ = 0;
        }
    }

    bool Enemy::canMove() {
        return coolDown_ == 0;
    }
}  // namespace entities
