#include "entity.hpp"

#include "displayable.hpp"

#include "display.hpp" // TODO: rimuovere questo import per le costanti di win quando si avrà il sistema per detection collisioni
#include "position.hpp"

Entity::Entity(int life, int attack, int defense, int shield): 
    Displayable(Position{1,1}, 'E'), 
    life_(life),
    attack_(attack),
    defense_(defense),
    shield_(shield) {}

Entity::Entity(int life, int attack, int defense, int shield,
    Position current,
    char displayChar): 
    Displayable(current, displayChar), 
    life_(life),
    attack_(attack),
    defense_(defense),
    shield_(shield) {}

void Entity::move() {}

bool Entity::canMove(int x, int y){
    return (x > 0 && y > 0) &&
        (x < manager::kGameWindowsSize.x - 1 && y < manager::kGameWindowsSize.y - 1);
}

bool Entity::isDead() {
    return life_ <= 0;
}

void Entity::attack(Entity *entity) {
    entity->applyDamage(attack_);
}

void Entity::applyDamage(int damage) {
    int damageAfterShield = damage - shield_;
    
    if (damageAfterShield > 0) {
        shield_ = 0; // rappresenta uno scudo rotto
        life_ -= (damageAfterShield - defense_);
    } else {
        shield_ -= damage;
    }
}

