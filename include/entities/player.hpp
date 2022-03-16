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
// Player: classe che contiene il personaggio
class Player: public Entity {
  private:
    // TODO inventario
  public:
    Player();

    // funzione che sarà chiamata dall'input del giocatore
    // TODO: ricerca il mostro da attaccare in un certo range
    // se trova applica il danno
    void attack();

    // TODO
    void pickup(); 
};