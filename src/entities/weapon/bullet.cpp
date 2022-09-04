#include "entities/weapon/bullet.hpp"

#include "gamestruct/logger.hpp"
#include "gamestruct/position.hpp"
#include "level/collidable.hpp"
#include "manager/level.hpp"

namespace weapon {
    Bullet::Bullet(Position position, enums::Direction direction, int damage)
        : Movable(position, '.'),
          damage_{damage},
          isDestroyed_(false) {
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

    bool Bullet::checkCollision(manager::Level *levelManager) {
        Position bulletNextPosition = this->getNextPosition();
        level::Collidable *collision = levelManager->getLevel()->getCollision(bulletNextPosition);
        Position bulletPosition = this->getPosition();
        level::Collidable *currCollision = levelManager->getLevel()->getCollision(bulletPosition);

        if (_handleCollision(levelManager, currCollision)) {
            return true;
        } else if (_handleCollision(levelManager, collision)) {
            return true;
        } else return false;
    }

    void Bullet::act(manager::Level *levelManager) {
        if (checkCollision(levelManager)) {
            isDestroyed_ = true;
        } else {
            this->move();
        }
    }

    bool Bullet::isDestroyed() const {
        return isDestroyed_;
    }

    void Bullet::render(WINDOW *win, bool force) {
        // evita la cancellazione del player guardando il carattere printato nello schermo attuale
        char lastChar = mvwinch(win, this->getLastPosition().riga, this->getLastPosition().colonna);
        if (lastChar != 'P' && lastChar != 'S') {
            this->clearLast(win);
            Displayable::render(win, force);
        }
    }

    bool Bullet::_handleCollision(manager::Level *levelManager, level::Collidable *collision) {
        if (collision == nullptr || collision->getCollisionType() == enums::CollisionType::NONE) {
            return false;
        }

        enums::CollisionType type = collision->getCollisionType();
        if (type == enums::CollisionType::ENTITY) {
            if (this->handleEntityHit((Entity *) collision)) {
                if (collision == levelManager->getPlayer()) {
                    levelManager->getLogQueue()->addEvent("Player sconfitto");
                } else {
                    levelManager->getPlayer()->incrementScore(500);
                    levelManager->getLogQueue()->addEvent("Nemico sconfitto");
                }
            } else {
                if (collision == levelManager->getPlayer()) {
                    levelManager->getLogQueue()->addEvent("Sei stato colpito da un proiettile");
                } else {
                    levelManager->getLogQueue()->addEvent("Nemico colpito da un proiettile");
                }
            }
        }
        
        return true;
    }
}  // namespace weapon
