#include "entities/entity.hpp"

#include "manager/level.hpp"
#include "enums/direction.hpp"
#include "enums/collision.hpp"

// TODO(simo): file di configurazione per i valori di default?? ha senso secondo te?? 
// perché questi valori di default per displayable hardcodati così sono un pò brutti
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

void Entity::move(manager::Level *levelManager) {
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

    if(isMoving) {
        switch (levelManager->getCollisionObject(Position(new_x, new_y))) {
            case enums::CollisionObject::WALL:
                break;
            case enums::CollisionObject::ENTITY: 
                // TODO(simo) può anche essere chiamato enemy invece di entity, obboh
                // decidi te poi dopo!
                break;
            case enums::CollisionObject::ARTIFACT:
                // TODO(simo)
                break;
            case enums::CollisionObject::NONE:
                setPosition(Position(new_x, new_y));
                break;
        }
    }
    
    this->direction_ = enums::Direction::NONE;
}

void Entity::setDirection(enums::Direction direction) {
    direction_ = direction;
}

bool Entity::isDead() const {
    return life_ <= 0;
}

void Entity::attack(Entity *entity) {
    // TODO(simo)
    // implementare l'attacco
}

void Entity::applyDamage(int damage) {
    life_ -= damage;
}

