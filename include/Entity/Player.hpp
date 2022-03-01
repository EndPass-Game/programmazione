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

class Player;

#include "Direction.hpp"
#include "Display.hpp"
#include "LevelManager.hpp"

class Player: public Display{
public:
    Direction direction; 
    Player();
    void move(LevelManager* level);
    bool canMove(int x,int y,LevelManager* level);
private:

};