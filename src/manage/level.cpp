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

#include "enemy.hpp"
#include "game_state.hpp"
#include "level.hpp"
#include "player.hpp"

namespace manager {
    Level::Level() {
        player = new Player();
        enemy = new Enemy();
        gameState = new Changeable<enums::GameState>(enums::GameState::RUNNING);
    }

    Level::~Level(){
        delete player;
        delete enemy;
        delete gameState;
    }
}