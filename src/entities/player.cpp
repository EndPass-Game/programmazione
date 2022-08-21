/*
Dati:
1. vite
2. posizione
3. danno

Funzioni
1. display
2. muovi
4. attacco
5. Interagisci (collectibles porte)
6. Mostra / non-mostrare Barra vita (?)

Altro
1. Inventario ( Classe apparte? )
*/
#include "entities/player.hpp"

#include "entities/entity.hpp"
#include "enums/collision-type.hpp"
#include "enums/direction.hpp"
#include "level/collidable.hpp"
#include "manager/level.hpp"

Player::Player()
    : Entity(12, 3,   // vita e attacco
             {1, 1},  // position di spawn
             'P'),    // charattere mostrato su schermo
      powers_(0),
      score_(0),
      coolDown_(0),
      coolDownMax_(10),  // può sparare ogni 5 frame
      logger_("Player") {}

void Player::addPower() {
    logger_.info("picked up power");
    this->powers_++;
}

void Player::setPosition(Position pos) {
    Displayable::setPosition(pos);
    nextPosition_ = Movable::_computeNextPosition(lastNotNullDirection_);
}

void Player::removePower() {
    logger_.info("used power");
    this->powers_--;
}

int Player::getPowers() {
    return powers_;
}

void Player::_handleDoorCollision(manager::Level *levelManager, level::DoorSegment *door) {
    logger_.info("collided with door");
    if (door->getNextLevelIdx() == -1) {
        int nextLevelIdx = levelManager->addLevel();
        door->setNextLevelIdx(nextLevelIdx);
    }

    if (door->isDoorOpen()) {
        logger_.info("moving to level with idx %d", door->getNextLevelIdx());
        levelManager->goToLevel(door->getNextLevelIdx());
    } else {
        if (levelManager->getPlayer()->getPowers() > 0) {
            logger_.info("opening door with idx %d", door->getNextLevelIdx());
            levelManager->getPlayer()->removePower();
            door->openDoor();
        }
    }
}

void Player::_handleWallCollision(manager::Level *levelManager, level::WallSegment *wall) {}

void Player::_handleEntityCollision(manager::Level *levelManager, Entity *entity) {}

void Player::_handleArtifactCollision(manager::Level *levelManager, collectables::Artifact *artifact) {
    levelManager->getPlayer()->setLife(levelManager->getPlayer()->getLife() + artifact->getLifeUpgrade());
    levelManager->getPlayer()->setPosition(nextPosition_);
    delete artifact;
}

void Player::_handlePowerCollision(manager::Level *levelManager, collectables::Power *power) {
    levelManager->getPlayer()->addPower();
    levelManager->getPlayer()->setPosition(nextPosition_);
    delete power;
}

void Player::_handleNoneCollision(manager::Level *levelManager) {
    levelManager->getPlayer()->setPosition(nextPosition_);
}

int Player::getScore() {
    return score_;
}

void Player::incrementScore(int increment) {
    score_ += increment;
}

void Player::resetCoolDown() {
    coolDown_ = coolDownMax_;
}

void Player::coolDown() {
    coolDown_--;
    if (coolDown_ < 0) {
        coolDown_ = 0;
    }
}

bool Player::canFire() {
    return coolDown_ == 0;
}