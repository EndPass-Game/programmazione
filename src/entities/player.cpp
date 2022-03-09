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
#include <mutex>

#include "player.hpp"

#include "direction.hpp"
#include "entity.hpp"

#include "display.hpp" // TODO: rimuovere questo import per le costanti di win quando si avrà il sistema per detection collisioni

Player::Player(): 
    Entity(12, 3, 0, 0, // TODO: gestire queste costanti hardcoded in un file di setting
    {1, 1}, /* position di spawn */ 
    'P'), 
    direction_(enums::NONE) {}

void Player::move(){
    std::lock_guard<std::mutex> lock(mutex);
    int new_x = getPosition().x, new_y = getPosition().y;
    bool isMoving = true;
    switch(this->direction_){
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

    if(isMoving and canMove(new_x, new_y)){
        setPosition({new_x, new_y});
    }
    
    this->direction_ = enums::Direction::NONE;
}

void Player::setDirection(enums::Direction direction) {
    std::lock_guard<std::mutex> lock(mutex);
    direction_ = direction;
}