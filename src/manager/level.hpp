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

#include "enums/game_state.hpp"
#include "entities/enemy.hpp"
#include "entities/player.hpp"
#include "gamestruct/changeable.hpp"
#include "gamestruct/changeable.hpp"
#include <mutex>

namespace manager {
    // Level manager: contiene tutte gli oggetti che vengono mostrati
    // nel gioco
    struct Level {
      private:
        std::mutex levelMutex;
      public:
        Level();
        ~Level();

        // la classe del giocatore principale
        Player *player;

        // TODO: dovrebbe essere sostituita da una struttura di dati
        // che contenga ogni nemico, in modo simile sarebbe buono
        // avere muri e artefatti
        Enemy *enemy; 

        Changeable<enums::GameState>* gameState;
    };
}