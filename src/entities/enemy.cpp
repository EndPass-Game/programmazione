#include "entities/enemy.hpp"

#include "entities/kamikaze.hpp"
#include "entities/shooter.hpp"
#include "entities/entity.hpp"
#include "enums/collision-type.hpp"
#include "enums/direction.hpp"
#include "level/collidable.hpp"
#include "manager/level.hpp"
namespace entities {
    Enemy::Enemy(char c)
        : Entity(12, 5,  // vita e attacco
                {4, 4},  // position di spawn
                 c),
          logger_("Enemy") {}

    Enemy::Enemy(Position spawnPos, int attack, char c)
        : Entity(12, attack, spawnPos, c),
          coolDown_(0),
          coolDownMax_(10),  // può muoversi ogni 10 frame
          logger_("Enemy") {}
    void Enemy::wander(Player *player) {
        enums::Direction directions[] = {
            enums::Direction::UP,
            enums::Direction::RIGHT,
            enums::Direction::LEFT,
            enums::Direction::DOWN,
            enums::Direction::NONE,
        };
        int direction = rand() % 5;
        this->setDirection(directions[direction]);
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

    void Enemy::act(manager::Level *levelManager) {
        if (canMove()) {
            wander(levelManager->getPlayer());
            move(levelManager);
            resetCoolDown();
        }
        moveCoolDown();
        attack(levelManager);
    }

}  // namespace entities
