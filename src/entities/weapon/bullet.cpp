#include "entities/weapon/bullet.hpp"

#include "gamestruct/logger.hpp"
namespace weapon {

    Bullet::Bullet(Position position, enums::Direction direction, int damage)
        : Movable(position, '.'),
          damage_{1} {
        Movable::setDirection(direction);
    }

    bool Bullet::hasHit() {
        return false;
    }

    bool Bullet::handleEntityHit(Entity *entity) {
        entity->applyDamage(damage_);
        return (entity->isDead());
    }

    void Bullet::move() {
        setPosition(nextPosition_);
        nextPosition_ = Movable::_computeNextPosition(direction_);
    }

}  // namespace weapon