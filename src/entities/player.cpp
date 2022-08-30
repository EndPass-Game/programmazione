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
      maxLife_(12),
      logger_("Player") {}

void Player::addPower() {
    logger_.info("picked up power");
    this->powers_++;
    this->life_ = maxLife_;
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
    if (door->isOpen()) {
        if (door->getNextLevelIdx() == -1) {
            levelManager->getLogQueue()->addEvent("Nuovo livello creato.");
            this->incrementScore(100);
            levelManager->generateLevel(door);
        }
        logger_.info("moving to level with idx %d", door->getNextLevelIdx());
        levelManager->getLogQueue()->addEvent("Cambiato livello");
        levelManager->goToLevel(door->getNextLevelIdx());
    } else {
        levelManager->getLogQueue()->addEvent("la porta e' chiusa, finisci il livello per aprirla");
    }
}

void Player::_handleWallCollision(manager::Level *levelManager, level::WallSegment *wall) {}

void Player::_handleEntityCollision(manager::Level *levelManager, Entity *entity) {}

void Player::_handleArtifactCollision(manager::Level *levelManager, collectables::Artifact *artifact) {
    datastruct::Vector<collectables::Artifact *> artifacts;
    level::Level *level = levelManager->getLevel();
    artifacts = level->getArtifacts();
    for (unsigned int i = 0; i < artifacts.size(); i++) {
        if (artifacts[i] == artifact) {
            level->deleteArtifact(i);
            break;
        }
    }
    levelManager->getLogQueue()->addEvent("Artefatto raccolto");
    this->incrementScore(100);
    this->setLife(this->getLife() + artifact->getLifeUpgrade());
    this->maxLife_ += artifact->getLifeUpgrade();
    this->setPosition(nextPosition_);

    if (level->isComplete()) {
        level->openAllDoors();
    }

    delete artifact;
}

void Player::_handlePowerCollision(manager::Level *levelManager, collectables::Power *power) {
    datastruct::Vector<collectables::Power *> powers;
    level::Level *currLevel = levelManager->getLevel();
    powers = currLevel->getPowers();
    for (unsigned int i = 0; i < powers.size(); i++) {
        if (powers[i] == power) {
            currLevel->deletePower(i);
            break;
        }
    }
    currLevel->openLocalDoor(power->getId());
    this->addPower();
    levelManager->getLogQueue()->addEvent("Hai raccolto un potere");
    this->incrementScore(100);
    this->setPosition(nextPosition_);
    delete power;
}

void Player::_handleNoneCollision(manager::Level *levelManager) {
    this->setPosition(nextPosition_);
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