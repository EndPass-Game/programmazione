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

Player::Player() : Entity(12, 3,  // TODO: gestire queste costanti hardcoded in un file di setting
                          {1, 1}, /* position di spawn */
                          'P')    /* charattere mostrato su schermo */
{
    powers_ = 0;
    score_ = 0;
}
// TODO
void Player::attack()
{
    logger_.info("attacking");
}

// TODO
void Player::pickup() {}

void Player::addPower()
{
    logger_.info("picked up power");
    this->powers_++;
}

void Player::removePower()
{
    logger_.info("used power");
    this->powers_--;
}

int Player::getPowers()
{
    return powers_;
}

int Player::getScore()
{
    return score_;
}

void Player::incrementScore(int increment)
{
    score_ += increment;
}