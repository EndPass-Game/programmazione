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

void Player::_handleArtifactCollision(manager::Level *levelManager, collectables::Artifact *artifact) {
    level::Level *level = levelManager->getLevel();
    char const* artefattoText = "Artefatto raccolto";
    levelManager->getLogQueue()->addEvent(artefattoText);
    char const* vitaText = "Aumentata la vita di: ";
    char* incrementLifeText = stringUtility::intToString(artifact->getLifeUpgrade());
    char* text = stringUtility::concat(vitaText, incrementLifeText);
    levelManager->getLogQueue()->addEvent(text);
    delete[] incrementLifeText;
    delete[] text;
    this->incrementScore(100);
    this->setLife(this->getLife() + artifact->getLifeUpgrade());
    this->maxLife_ += artifact->getLifeUpgrade();
    this->setPosition(nextPosition_);

    levelManager->getLevel()->deleteCollidable((Collidable *) artifact);

    if (level->isComplete()) {
        level->openAllDoors();
    }
}

void Player::_handlePowerCollision(manager::Level *levelManager, collectables::Power *power) {
    level::Level *currLevel = levelManager->getLevel();
    currLevel->openLocalDoor(power->getId());
    this->addPower();
    levelManager->getLogQueue()->addEvent("Hai raccolto un potere");
    this->incrementScore(100);
    this->setPosition(nextPosition_);
    currLevel->deleteCollidable((Collidable *) power);
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

void Player::attack(manager::Level *levelManager) {
    if (!this->canFire()) {
        return;
    }
    level::Level *level = levelManager->getLevel();

    this->resetCoolDown();
    logger_.info("player firing a bullet");
    Position bulletPosition = this->getNextPosition();
    logger_.debug("next position: %d, %d", bulletPosition.colonna, bulletPosition.riga);
    logger_.debug("curr position: %d, %d", this->getPosition().colonna, this->getPosition().riga);
    level::Collidable *collision = level->getCollision(bulletPosition);
    if (collision == nullptr) {
        weapon::Bullet *bullet = new weapon::Bullet(bulletPosition, this->getLastNotNullDirection(), this->getAttack());
        level->addBullet(bullet);
    } else if (collision->getCollisionType() == enums::CollisionType::ENTITY) {
        weapon::Bullet *bullet = new weapon::Bullet(this->getPosition(), this->getLastNotNullDirection(), this->getAttack());
        level->addBullet(bullet);
    }
}

void Player::act(manager::Level *levelManager) {
    this->move(levelManager);
    this->coolDown();
}