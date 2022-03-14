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

#include "game_state.hpp"
#include "player.hpp"
#include "changeable.hpp"
#include <mutex>

namespace manager {
    // Level manager:contiene tutte gli oggetti che vengono mostrati
    // nel gioco

    // TODO: come descritto nel commento di commit, per le interfacce present qui
    // questo dovrebbe essere una struct, ma essendo un manager questo simbolo
    // dovrebbe fare molto di più (come costruzione dell'ambiente schermo)
    // bisogna definire meglio le responsabilità di questo level manager
    struct Level {
      private:
        //
        std::mutex levelMutex;
      public:
        Level();
        ~Level();

        void getCurrentGameState(enums::GameState game);
        //la classe del giocatore principale
        Player* player;
        Changeable<enums::GameState>* gameState;


    };
}