#include "entities/entity.hpp"

#include "enums/collision-type.hpp"
#include "enums/direction.hpp"
#include "level/collidable.hpp"
#include "manager/level.hpp"

// perché questi valori di default per displayable hardcodati così sono un pò brutti
Entity::Entity(int life, int attack)
    : Movable(Position{1, 1}, 'E'),
      life_(life),
      attack_(attack) {}

Entity::Entity(int life, int attack, Position current, char displayChar)
    : Movable(current, displayChar),
      life_(life),
      attack_(attack) {}

void Entity::move(manager::Level *levelManager) {
    if (direction_ == enums::Direction::NONE) {
        return;
    }

    lastNotNullDirection_ = direction_;
    nextPosition_ = _computeNextPosition(direction_);
    direction_ = enums::Direction::NONE;

    level::Collidable *collision = levelManager->getCollision(nextPosition_, levelManager);
    enums::CollisionType type = enums::CollisionType::NONE;
    if (collision != nullptr) type = collision->getCollisionType();
    switch (type) {
        case enums::CollisionType::DOORSEGMENT:
            _handleDoorCollision(levelManager, (level::DoorSegment *) collision);
            break;
        case enums::CollisionType::WALLSEGMENT:
            _handleWallCollision(levelManager, (level::WallSegment *) collision);
            break;
        case enums::CollisionType::ENTITY:
            _handleEntityCollision(levelManager, (Entity *) collision);
            break;
        case enums::CollisionType::ARTIFACT:
            _handleArtifactCollision(levelManager, (collectables::Artifact *) collision);
            break;
        case enums::CollisionType::POWER:
            _handlePowerCollision(levelManager, (collectables::Power *) collision);
            break;
        case enums::CollisionType::NONE:
            _handleNoneCollision(levelManager);
            break;
    }
    nextPosition_ = _computeNextPosition(lastNotNullDirection_);
}

bool Entity::isDead() const {
    return life_ <= 0;
}

void Entity::attack(Entity *entity) {
    entity->applyDamage(attack_);
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

void Entity::_handleDoorCollision(manager::Level *levelManager, level::DoorSegment *door) {}
void Entity::_handleWallCollision(manager::Level *levelManager, level::WallSegment *wall) {}
void Entity::_handleEntityCollision(manager::Level *levelManager, Entity *entity) {}
void Entity::_handleArtifactCollision(manager::Level *levelManager, collectables::Artifact *artifact) {}
void Entity::_handlePowerCollision(manager::Level *levelManager, collectables::Power *power) {}
void Entity::_handleNoneCollision(manager::Level *levelManager) {}
