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
#include "level/collidable.hpp"
#include "level/level.hpp"
#include "datastruct/vector.hpp"
#include "gamestruct/size.hpp"
#include "gamestruct/state-watcher.hpp"
#include "gamestruct/logger.hpp"
#include "loader/directory-loader.hpp"
namespace manager {
    // Level manager: contiene tutte gli oggetti che vengono mostrati
    // nel gioco
    class Level {
      private: 
        datastruct::Vector<level::Level *> levels_;
        Player *player_;
        StateWatcher<int> *levelIdx_;
        loader::DirectoryLoader *dirLoader_; 

        Logger logger_ = Logger("manager::Level");
      public:
        Level();
        ~Level();

        Player *getPlayer();

        // @returns l'index del livello creato
        int addLevel();

        // stampa a schermo il livello scelto, se non è presente tale livello (indice invalido)
        // allora ritorna false, altrimenti true; 
        void goToLevel(int level);

        level::Collidable *getCollision(Position pos);

        void render(WINDOW *win, bool force);
    };
}