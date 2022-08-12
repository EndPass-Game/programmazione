#include "entities/entity.hpp"

#include "enums/collision-type.hpp"
#include "enums/direction.hpp"
#include "level/collidable.hpp"
#include "manager/level.hpp"

// TODO(simo): file di configurazione per i valori di default?? ha senso secondo te??
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
        collectables::Artifact *art;
        switch (type) {
            case enums::CollisionType::DOORSEGMENT:
                _handleDoorCollision(levelManager, (level::DoorSegment *) collision);
                break;
            case enums::CollisionType::WALLSEGMENT:
                break;
            case enums::CollisionType::ENTITY:
                // TODO(simo) può anche essere chiamato enemy invece di entity, obboh
                // decidi te poi dopo!
                break;
            case enums::CollisionType::ARTIFACT:  // TODO(simo): da spostare in Player
                art = dynamic_cast<collectables::Artifact *>(collision);
                levelManager->getPlayer()->setLife(levelManager->getPlayer()->getLife() + art->getLifeUpgrade());
                setPosition(Position(new_x, new_y));
                levelManager->getPlayer()->incrementScore(2);
                levelManager->getLogQueue()->addEvent("Hai raccolto un artefatto, aumenta la  vita!");
                delete art;
                break;
            case enums::CollisionType::NONE:
                setPosition(Position(new_x, new_y));
                break;
            case enums::CollisionType::POWER:
                levelManager->getPlayer()->addPower();
                setPosition(Position(new_x, new_y));
                levelManager->getPlayer()->incrementScore(5);
                levelManager->getLogQueue()->addEvent("Hai raccolto un potere!Puoi sbloccare  una porta!");

                delete (collectables::Power *) collision;
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

// TODO(ang): muovere a player, non vogliamo che entities si muovano per le porte (o sì?)
void Entity::_handleDoorCollision(manager::Level *levelManager, level::DoorSegment *door) {
    logger_.info("collided with door");
    if (door->getNextLevelIdx() == -1) {
        logger_.debug("facing direction is %d", door->getFacingDir());

        int nextLevelIdx = levelManager->addLevel(door->getFacingDir());
        door->setNextLevelIdx(nextLevelIdx);
    }

    if (door->isDoorOpen()) {
        logger_.info("moving to level with idx %d", door->getNextLevelIdx());
        levelManager->goToLevel(door->getNextLevelIdx());
        levelManager->getLogQueue()->addEvent("Hai cambiato livello!");
    } else {
        if (levelManager->getPlayer()->getPowers() > 0) {
            logger_.info("opening door with idx %d", door->getNextLevelIdx());
            levelManager->getPlayer()->removePower();
            door->openDoor();  // temporaneo
            levelManager->getPlayer()->incrementScore(10);
            levelManager->getLogQueue()->addEvent("nuovo livello");
        } else {
            levelManager->getLogQueue()->addEvent("la porta è chiusa");
        }
    }
}