/*
Dati
1. mappa successiva
2. porta aprta
3. muri
4. entità
5. prima porta
6. stanze

Funzioni:




*/
#pragma once

class LevelManager;

#include "GameStateEnum.hpp"
#include "Player.hpp"



class LevelManager{
private:
public:
    Player* player;
    GameState gameState;
    const int WINDOWS_SIZE_X=15;
    const int WINDOWS_SIZE_Y=25;
    LevelManager();

};