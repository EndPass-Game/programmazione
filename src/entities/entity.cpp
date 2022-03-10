#include "entity.hpp"

#include "displayable.hpp"
#include "direction.hpp"
#include "display.hpp" // TODO: rimuovere questo import per le costanti di win quando si avrà il sistema per detection collisioni
#include "position.hpp"

Entity::Entity(int life, int attack, int defense, int shield): 
    Displayable(Position{1,1}, 'E'), 
    life_(life),
    attack_(attack),
    defense_(defense),
    shield_(shield),
    direction_(enums::Direction::NONE) {}

Entity::Entity(int life, int attack, int defense, int shield,
    Position current,
    char displayChar): 
    Displayable(current, displayChar), 
    life_(life),
    attack_(attack),
    defense_(defense),
    shield_(shield),
    direction_(enums::Direction::NONE) {}

bool Entity::canMove(int x, int y) const {
    return (x > 0 && y > 0) &&
        (x < manager::kGameWindowsSize.x - 1 && y < manager::kGameWindowsSize.y - 1);
}

void Entity::move() {
    std::lock_guard<std::mutex> lock(mutex_);
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

void Entity::attack(Entity *entity) {
    std::lock_guard<std::mutex> lock(mutex_); // TODO: serve sto mutex qui?
    entity->applyDamage(attack_);
}

void Entity::applyDamage(int damage) {
    std::lock_guard<std::mutex> lock(mutex_);
    int damageAfterShield = damage - shield_;
    
    if (damageAfterShield > 0) {
        shield_ = 0; // rappresenta uno scudo rotto
        life_ -= (damageAfterShield - defense_);
    } else {
        shield_ -= damage;
    }
}

