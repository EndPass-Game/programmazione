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
#include "manager/level.hpp"
#include "enums/direction.hpp"
#include "enums/collision-type.hpp"
#include "level/collidable.hpp"


Player::Player(): 
    Entity(12, 3, // TODO: gestire queste costanti hardcoded in un file di setting
    {1, 1}, /* position di spawn */ 
    'P') /* charattere mostrato su schermo */ {
        powers_=0;
}
// TODO
void Player::attack() {
    logger_.info("attacking");
}

// TODO
void Player::pickup() {}

void Player::addPower(){
    logger_.info("picked up power");
    this->powers_++;
}

void Player::removePower(){
    logger_.info("used power");
    this->powers_--;
}

int Player::getPowers(){
    return powers_;
}

void Player::_handleDoorCollision(manager::Level *levelManager, level::DoorSegment *door, Position pos) {
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

void Player::_handleWallCollision(manager::Level *levelManager, level::WallSegment *wall, Position pos){

}

void Player::_handleEntityCollision(manager::Level *levelManager, Entity *entity, Position pos){
    
}

void Player::_handleArtifactCollision(manager::Level *levelManager, collectables::Artifact *artifact, Position pos){
    collectables::Artifact *art;
    art = dynamic_cast<collectables::Artifact *>(artifact);
    levelManager->getPlayer()->setLife(levelManager->getPlayer()->getLife() + art->getLifeUpgrade());
    levelManager->getPlayer()->setPosition(pos);
    delete art;
}

void Player::_handlePowerCollision(manager::Level *levelManager, collectables::Power *power, Position pos){
    levelManager->getPlayer()->addPower();
    levelManager->getPlayer()->setPosition(pos);
}

void Player::_handleNoneCollision(manager::Level *levelManager, Position pos){
    levelManager->getPlayer()->setPosition(pos);
}
