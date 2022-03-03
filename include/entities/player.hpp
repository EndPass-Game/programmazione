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

#include "direction.hpp"
#include "displayable.hpp"

// Player: classe che contiene il personaggio
// estende Display
class Player: public Displayable {
  private:
    // Contiene la direzione che dovrà essere intrapresa nel prossimo frame
    enums::Direction direction_;
  public:
    Player();

    // è muovrere il player nella direction settata
    void move();

    bool canMove(int x, int y);

    void setDirection(enums::Direction direction);
};