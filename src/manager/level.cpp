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
#include "level/collidable.hpp"
#include "gamestruct/size.hpp"
namespace manager
{
    Level::Level() {
        player_ = new Player();
        currentLevelIndex_ = -1; // -1 indica che non è stato ancora caricato nessun livello
    }

    Level::Level(Size size) {
        player_ = new Player();
        levels_.push_back(new level::Level(size));
        currentLevelIndex_ = 0;
    }

    Level::~Level() {
        for (unsigned int i = 0; i < levels_.size(); i++) {
            delete levels_[i];
        }
        delete player_;
    }

    Player *Level::getPlayer() {
        return player_;
    }

    void Level::addLevel() {
        // TODO(ang): fix level screen size
        levels_.push_back(new level::Level(levelScreenSize_));
    }

    level::Collidable *Level::getCollision(Position pos) {
        return levels_[currentLevelIndex_]->getCollision(pos);
    }

    bool Level::loadLevel(int level) {
        levels_[currentLevelIndex_]->setLastPlayerPosition(player_->getPosition());
        if (level < 0 || level >= (int) levels_.size()) {
            return false;
        }
        currentLevelIndex_ = level;
        player_->setPosition(levels_[currentLevelIndex_]->getLastPlayerPosition());
        return true;
    }

    void Level::render(WINDOW *win, bool force) {
        player_->clearLast(win);
        player_->render(win, force);
        levels_[currentLevelIndex_]->render(win, force);
        // TODO(ang): print player ( valuta se è meglio printarlo qui o in level/level 
        // io pensavo fosse meglio il level/level (gio))
    }
}