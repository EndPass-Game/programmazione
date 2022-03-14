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
//TODO:refactor mettere displayable come superclasse di entity e mettere
//entiti come superclasse di Player
class Player: public Displayable {
  private:
    // Contiene la direzione che dovrà essere intrapresa nel prossimo frame
    enums::Direction direction_;
    //aggiunta la thread safe
    std::mutex mutex;
  public:
    Player();

    //cambia le cordinate del player in base direzione settata in precedenza 
    //se è possibile andarci
    void move();

    //funzione che fa il check se è possibile andare in una certa posizione
    bool canMove(int x, int y);

    //setta la direzione del player 
    void setDirection(enums::Direction direction);
};