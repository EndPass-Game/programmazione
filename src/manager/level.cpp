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
#include "loader/loader-handler.hpp"
namespace manager
{
    Level::Level() {
        player_ = new Player();
        levelIdx_ = new StateWatcher<int>(-1); // -1 indica che non è stato ancora caricato nessun livello
        dirLoader_ = new loader::DirectoryLoader();

        int newLevelIdx = addLevel();
        levelIdx_->setCurrent(newLevelIdx);
        goToLevel(newLevelIdx); 
    }

    Level::~Level() {
        for (unsigned int i = 0; i < levels_.size(); i++) {
            delete levels_[i];
        }
        delete levelIdx_;
        delete player_;
        delete dirLoader_;
    }

    Player *Level::getPlayer() {
        return player_;
    }

    int Level::addLevel() {
        const char *levelToLoadName = dirLoader_->getRandomFileName();
        loader::LoaderHandler loader(levelToLoadName);

        if (levelIdx_->getCurrent() == -1) {
            levels_.push_back(new level::Level(&loader));
        } else {
            levels_.push_back(new level::Level(&loader, levelIdx_->getCurrent()));
        }
        return (int) levels_.size() - 1;
    }

    level::Collidable *Level::getCollision(Position pos) {
        return levels_[levelIdx_->getCurrent()]->getCollision(pos);
    }

    void Level::goToLevel(int levelIdx) {
        if (levelIdx < 0 || levelIdx >= (int) levels_.size()) {
            return;
        }
        levels_[levelIdx_->getCurrent()]->setLastPlayerPosition(player_->getPosition());
        levelIdx_->setCurrent(levelIdx);
        player_->setPosition(levels_[levelIdx_->getCurrent()]->getLastPlayerPosition());
        return;
    }

    void Level::render(WINDOW *win, bool force) {
        if (levelIdx_->isChanged()) {
            force = true;
            levels_[levelIdx_->getLast()]->clear(win);
        }

        player_->clearLast(win);
        player_->render(win, force);

        levels_[levelIdx_->getCurrent()]->render(win, force);
        // TODO(ang): print player ( valuta se è meglio printarlo qui o in level/level 
        // io pensavo fosse meglio il level/level (gio))
    }
}