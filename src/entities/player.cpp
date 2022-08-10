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

void Player::move(manager::Level *levelManager) {
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
        level::Collidable *collision = levelManager->getCollision(Position{new_x, new_y});
        enums::CollisionType type = enums::CollisionType::NONE; 
        if (collision != nullptr) type = collision->getCollisionType(); 
        collectables::Artifact *art;
        switch (type) {
            case enums::CollisionType::DOORSEGMENT:
                _handleDoorCollision(levelManager, (level::DoorSegment*) collision);
                break;
            case enums::CollisionType::WALLSEGMENT:
                break;
            case enums::CollisionType::ENTITY: 
                // TODO(simo) può anche essere chiamato enemy invece di entity, obboh
                // decidi te poi dopo!
                break;
            case enums::CollisionType::ARTIFACT: // TODO(simo): da spostare in Player
                art = dynamic_cast<collectables::Artifact *>(collision);
                levelManager->getPlayer()->setLife(levelManager->getPlayer()->getLife() + art->getLifeUpgrade());
                setPosition(Position(new_x, new_y));
                delete art;
                break;
            case enums::CollisionType::NONE:
                setPosition(Position(new_x, new_y));
                break;
            case enums::CollisionType::POWER:
                levelManager->getPlayer()->addPower();
                setPosition(Position(new_x, new_y));
                delete (collectables::Power *) collision;
                break;
        }
    }
    
    this->direction_ = enums::Direction::NONE;
}
