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
#include "manager/level.hpp"

#include "entities/player.hpp"
#include "entities/enemy.hpp"

namespace manager
{
    Level::Level()
    {
        player = new Player();
        enemy = new Enemy();
    }

    Level::~Level()
    {
        delete player;
        delete enemy;
    }
}