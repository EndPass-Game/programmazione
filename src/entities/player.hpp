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

#include "enums/direction.hpp"
#include "entities/entity.hpp"
#include "gamestruct/displayable.hpp"
#include "gamestruct/position.hpp"
#include "gamestruct/logger.hpp"
#include "level/collidable.hpp"
#include "level/door-segment.hpp"

// Player: classe che contiene il personaggio
class Player: public Entity {
  private:
    // TODO inventario
    int powers_;
    Logger logger_ = Logger("player");
  public:
    Player();

    // funzione che sarà chiamata dall'input del giocatore
    // TODO: ricerca il mostro da attaccare in un certo range
    // se trova applica il danno
    void attack();

    // TODO
    void pickup();

    void addPower();

    void removePower();
    
    int getPowers();

    // muove il player secondo la direzione impostata
    void move(manager::Level *levelManager);
};