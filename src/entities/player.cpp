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
    Entity(12, 3, // TODO: gestire queste costanti hardcoded in un file di setting
    {1, 1}, /* position di spawn */ 
    'P') /* charattere mostrato su schermo */ {}
// TODO
void Player::attack() {}

// TODO
void Player::pickup() {}
