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

#include <ncurses.h>

#include "entities/player.hpp"
#include "entities/enemy.hpp"
#include "gamestruct/size.hpp"
namespace manager
{
    Level::Level() {
        player_ = new Player();
        levelScreenSize_ = Size(0, 0);
        currentLevelIndex_ = -1; // -1 indica che non è stato ancora caricato nessun livello
    }

    Level::Level(Size size) {
        #include "gamestruct/logger.hpp"
        Logger().log("Level::Level(Size size)\n");
        player_ = new Player();
        levelScreenSize_ = size;
        Logger().log("da level manager: %d %d\n", size.riga, size.colonna);

        Logger().log("before level Level::Level(Size size)\n");
        levels_.push_back(new level::Level(levelScreenSize_));
        Logger().log("after level Level::Level(Size size)\n");

        currentLevelIndex_ = 0;
        Logger().log("end Level::Level(Size size)\n");

    }

    Player *Level::getPlayer() {
        return levels_[currentLevelIndex_]->getPlayer();
    }

    void Level::addLevel() {
        levels_.push_back(new level::Level(levelScreenSize_));
    }

    bool Level::loadLevel(int level) {
        if (level < 0 || level >= levels_.size()) {
            return false;
        }
        currentLevelIndex_ = level;
        return true;
    }

    void Level::render(WINDOW *win, bool force) {
        levels_[currentLevelIndex_]->render(win, force);
    }
}