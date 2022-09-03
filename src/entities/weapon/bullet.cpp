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

        // TODO: fai funzionare per la collisione attuale dopo
        // Position bulletPosition = this->getPosition();
        // level::Collidable *currCollision = getCollision(bulletPosition);

        enums::CollisionType type = enums::CollisionType::NONE;
        if (collision != nullptr) type = collision->getCollisionType();
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
                    levelManager->getLogQueue()->addEvent("Player colpito da un proiettile");
                } else {
                    levelManager->getLogQueue()->addEvent("Nemico colpito da un proiettile");
                }
            }
            return true;
        } else if (type == enums::CollisionType::NONE) {
            return false;
        } else {
            return true;
        }
        return false;
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
        char currChar = mvwinch(win, this->getPosition().riga, this->getPosition().colonna);
        if (currChar == 'P' || currChar == 'S') {
            this->clearLast(win);
        }
        Displayable::render(win, force);
    }
}  // namespace weapon
