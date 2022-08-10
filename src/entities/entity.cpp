#include "entities/entity.hpp"

#include "manager/level.hpp"
#include "enums/direction.hpp"
#include "enums/collision-type.hpp"
#include "level/collidable.hpp"

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

int Entity::getLife(){
    return life_;
}

void Entity::setLife(int life){
    this->life_=life;
}

enums::CollisionType Entity::getCollisionType() {
    return enums::CollisionType::ENTITY;
}

// TODO(ang): muovere a player, non vogliamo che entities si muovano per le porte (o sì?)
void Entity::_handleDoorCollision(manager::Level *levelManager, level::DoorSegment *door) {
    logger_.info("collided with door");
    if (door->getNextLevelIdx() == -1) {
        int nextLevelIdx = levelManager->addLevel();
        door->setNextLevelIdx(nextLevelIdx);
    }

    if (door->isDoorOpen()) {
        logger_.info("moving to level with idx %d", door->getNextLevelIdx());
        levelManager->goToLevel(door->getNextLevelIdx());
    } else {
        if(levelManager->getPlayer()->getPowers() > 0){
            logger_.info("opening door with idx %d", door->getNextLevelIdx());
            levelManager->getPlayer()->removePower();
            door->openDoor(); // temporaneo
        }
    }
}