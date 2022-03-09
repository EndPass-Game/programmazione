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
#pragma once

#include "entity.hpp"
#include "direction.hpp"
// Player: classe che contiene il personaggio
// estende Display
class Player: public Entity {
  private:
    // Contiene la direzione che dovrà essere intrapresa nel prossimo frame
    enums::Direction direction_;
    //aggiunta la thread safe
    std::mutex mutex;
  public:
    Player();

    // Muove il player nella direction settata, sovrascrive il virtual
    // in entity
    void move();

    // funzione che sarà chiamata dall'input del giocatore
    void attack(); 

    //setta la direzione del player 
    void setDirection(enums::Direction direction);
};