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

Player::Player(): 
    Entity(12, 3, // TODO: gestire queste costanti hardcoded in un file di setting
    {1, 1}, /* position di spawn */ 
    'P') /* charattere mostrato su schermo */ {}
// TODO
void Player::attack() {}

// TODO
void Player::pickup() {}


void Player::handleCollision(manager::Level *levelManager, enums::CollisionObject collisionObject) {
    switch (collisionObject) {
        case enums::CollisionObject::DOOR:
        //1. salvare posizione attuale (si sa già)
        ///2. loaddare il livello corrispondente alla porta???  


        if 
        Una soluzione possibile: 
        dare la posizione in cui volevi muoverti
        poi il levelManager ricava la porta 


        // modo separa le cose.... 
        levelManager().caricaLivello = (oldPosition, nextPositione) => {
            door = getDoor(nextPosizione); 
            if (door != nullptr) {
                loadLevel(door.Info, oldPosition); // + vecchia posizione su informazione attuale
            }
        } 

        levelManager().caricaNuovo(posizione attuale)
        chiama funzione per cambiare il livello (salvandosi la posizione attuale )


        // di cosa ha bisogno questo?  
        levelManager.loadLevel();

            break;



        // nel caso del muro.  
        // chiamare al levelmanger funzione 
        // per loaddare il muro corrispondente. (se conoscesse vecchia posizione)
        // chiamare levelManger 


    }
}