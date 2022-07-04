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

#include <ncurses.h>

#include "entities/player.hpp"
#include "enums/collision.hpp"
#include "level/level.hpp"
#include "datastruct/vector.hpp"
#include "gamestruct/size.hpp"

namespace manager {
    // Level manager: contiene tutte gli oggetti che vengono mostrati
    // nel gioco
    class Level {
      private: 
        datastruct::Vector<level::Level *> levels_;
        Player *player_;
        Size levelScreenSize_;
        int currentLevelIndex_;
      public:
        Level();
        Level(Size size);
        ~Level();

        Player *getPlayer();
        void addLevel();

        // stampa a schermo il livello scelto, se non è presente tale livello (indice invalido)
        // allora ritorna false, altrimenti true; 
        bool loadLevel(int level);

        enums::CollisionObject getCollisionObject(Position pos);

        void render(WINDOW *win, bool force);
    };
}