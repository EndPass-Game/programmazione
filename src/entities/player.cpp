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
#include "entity.hpp"

Player::Player(): 
    Entity(12, 3, 0, 0, // TODO: gestire queste costanti hardcoded in un file di setting
    {1, 1}, /* position di spawn */ 
    'P'), /* charattere mostrato su schermo */ 
    hasActed_(true) {}

bool Player::hasActed() const {
    return hasActed_;
}

void Player::resetAction() {
    hasActed_ = false;
}

void Player::move() {
    if (hasActed_) return;

    Entity::move();
    if (position_->isChanged()) hasActed_ = true;
}

// TODO
void Player::attack() {
    if (hasActed_) return;
    hasActed_ = true;
}

// TODO
void Player::pickup() {
    if (hasActed_) return;
    hasActed_ = true;
}