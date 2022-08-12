#include "entities/entity.hpp"

#include "enums/collision-type.hpp"
#include "enums/direction.hpp"
#include "level/collidable.hpp"
#include "manager/level.hpp"

// perché questi valori di default per displayable hardcodati così sono un pò brutti
Entity::Entity(int life, int attack)
    : Displayable(Position{1, 1}, 'E'),
      life_(life),
      attack_(attack),
      direction_(enums::Direction::NONE) {}

Entity::Entity(int life, int attack, Position current, char displayChar)
    : Displayable(current, displayChar),
      life_(life),
      attack_(attack),
      direction_(enums::Direction::NONE) {}

void Entity::move(manager::Level *levelManager) {
    int new_x = getPosition().riga, new_y = getPosition().colonna;
    bool isMoving = true;
    switch (this->direction_) {
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

    if (isMoving) {
        level::Collidable *collision = levelManager->getCollision(Position{new_x, new_y});
        enums::CollisionType type = enums::CollisionType::NONE;
        if (collision != nullptr) type = collision->getCollisionType(); 
        switch (type) {
            case enums::CollisionType::DOORSEGMENT:
                _handleDoorCollision(levelManager, (level::DoorSegment*) collision, Position(new_x, new_y));
                break;
            case enums::CollisionType::WALLSEGMENT:
                _handleWallCollision(levelManager, (level::WallSegment*) collision, Position(new_x, new_y));
                break;
            case enums::CollisionType::ENTITY: 
                _handleEntityCollision(levelManager, (Entity*) collision, Position(new_x, new_y));
                break;
            case enums::CollisionType::ARTIFACT:
                _handleArtifactCollision(levelManager, (collectables::Artifact*) collision, Position(new_x, new_y));
                break;
            case enums::CollisionType::POWER:
                _handlePowerCollision(levelManager, (collectables::Power*) collision, Position(new_x, new_y));
                delete (collectables::Power *) collision;
                break;
            case enums::CollisionType::NONE:
                _handleNoneCollision(levelManager, Position(new_x, new_y));
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

int Entity::getLife() {
    return life_;
}

void Entity::setLife(int life) {
    this->life_ = life;
}

enums::CollisionType Entity::getCollisionType() {
    return enums::CollisionType::ENTITY;
}

void Entity::_handleDoorCollision(manager::Level *levelManager, level::DoorSegment *door, Position pos) {
    
}

void Entity::_handleWallCollision(manager::Level *levelManager, level::WallSegment *wall, Position pos){

}

void Entity::_handleEntityCollision(manager::Level *levelManager, Entity *entity, Position pos){
    
}

void Entity::_handleArtifactCollision(manager::Level *levelManager, collectables::Artifact *artifact, Position pos){

}

void Entity::_handlePowerCollision(manager::Level *levelManager, collectables::Power *power, Position pos){

}

void Entity::_handleNoneCollision(manager::Level *levelManager, Position pos){

}