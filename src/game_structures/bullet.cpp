
#include "bullet.hpp"
#include "display.hpp" // gamewindowssize
#include "displayable.hpp"
#include "direction.hpp"
#include "entity.hpp"
#include "position.hpp"

Bullet::Bullet(Position position, enums::Direction direction):
    Displayable(position, '.'),
    direction_(direction),
    damage_{1} {}

// TODO(SIMO): modfiicare a seconda del collision detector
// attualmente guarda solo i bordi
bool Bullet::hasHit() {
    int x = getPosition().x;
    int y = getPosition().y;
    return !Displayable::collisionDetection(x, y);
}

void Bullet::handleEntityHit(Entity *entity) {
    entity->applyDamage(damage_);
}

void Bullet::move() {
    int new_x = getPosition().x, new_y = getPosition().y;
    bool isMoving = true;
    switch(this->direction_) {
        case enums::Direction::UP:
            new_x -= 1;
            break;
        case enums::Direction::RIGHT:
            new_y += 1;
            break;
        case enums::Direction::LEFT:
            new_y -= 1;
            break;
        case enums::Direction::DOWN:
            new_x += 1;
            break;
        case enums::Direction::NONE:
            // non dovremmo mai avere un proiettile fermo
            // per completezza di switch esiste anche questo ramo.
            isMoving = false;
            break;
    }

    if(isMoving) {
        setPosition({new_x, new_y});
    }
}