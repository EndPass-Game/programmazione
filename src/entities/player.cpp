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
#include "player.hpp"

#include "direction.hpp"
#include "displayable.hpp"

#include "display.hpp" // TODO: rimuovere questo import per le costanti di win quando si avrà il sistema per detection collisioni

Player::Player(): Displayable(Position{1,1}, 'P'), direction_(enums::NONE){}

void Player::move(){
    int new_x = getPosition().x, new_y = getPosition().y;
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
            // TODO: creare un modo migliore per uscire dalla funzione
            // invece che un return qui
            return;
            break;
    }

    if(canMove(new_x, new_y)){
        movePosition({new_x, new_y});
    }
    
    this->direction_ = enums::Direction::NONE;
}

bool Player::canMove(int x, int y){
    return (x > 0 && y > 0) &&
        (x < manager::kWindowSizeX - 1 && y < manager::kWindowSizeY - 1);
}

void Player::setDirection(enums::Direction direction) {
    direction_ = direction;
}