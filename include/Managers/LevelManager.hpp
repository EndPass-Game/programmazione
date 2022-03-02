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


// Level manager:contiene tutte gli oggetti che vengono mostrati
// nel gioco
class LevelManager{
private:
public:
    //la classe del giocatore principale
    Player* player;
    //Enum che identifica lo stato del gioco
    GameState gameState;

    //La size della schermata dove è contenuto il gioco
    const int WINDOWS_SIZE_X=15;
    //La size della schermata dove è contenuto il gioco
    const int WINDOWS_SIZE_Y=25;


    LevelManager();

};