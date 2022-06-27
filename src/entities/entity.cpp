#include "entities/entity.hpp"

#include "enums/direction.hpp"
#include "gamestruct/displayable.hpp"
#include "gamestruct/position.hpp"
#include "manager/display.hpp" // TODO: rimuovere questo import per le costanti di win quando si avrà il sistema per detection collisioni

Entity::Entity(int life, int attack): 
    Displayable(Position{1,1}, 'E'), 
    life_(life),
    attack_(attack),
    direction_(enums::Direction::NONE) {}

Entity::Entity(int life, int attack, Position current, char displayChar): 
    Displayable(current, displayChar), 
    life_(life),
    attack_(attack),
    direction_(enums::Direction::NONE) {}

bool Entity::canMove(int x, int y) const {
    return (x > 0 && y > 0) &&
        (x < manager::kGameWindowsSize.riga - 1 && y < manager::kGameWindowsSize.colonna - 1);
}

void Entity::move() {
    std::lock_guard<std::mutex> lock(mutex_);
    int new_x = getPosition().riga, new_y = getPosition().colonna;
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
            isMoving = false;
            break;
    }

    if(isMoving and canMove(new_x, new_y)) {
        setPosition({new_x, new_y});
    }
    
    this->direction_ = enums::Direction::NONE;
}

void Entity::setDirection(enums::Direction direction) {
    std::lock_guard<std::mutex> lock(mutex_);
    direction_ = direction;
}

bool Entity::isDead() const {
    return life_ <= 0;
}

void Entity::attack(Entity *entity) {}

void Entity::applyDamage(int damage) {
    std::lock_guard<std::mutex> lock(mutex_);
    life_ -= damage;
}

