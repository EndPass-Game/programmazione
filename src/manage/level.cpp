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

#include "game_state.hpp"
#include "level.hpp"
#include "player.hpp"

namespace manager {
    Level::Level() {
        gameState = enums::GameState::RUNNING; 
        player = new Player();
    }
}