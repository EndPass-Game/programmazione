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
        levelIdx_ = new StateWatcher<int>(-1); // -1 indica che non è stato ancora caricato nessun livello
    }

    Level::Level(Size size) {
        player_ = new Player();
        levels_.push_back(new level::Level(size));
        levelIdx_ = new StateWatcher<int>(0);
        levelScreenSize_ = size; // TODO: sostituire questo con size globale

        // TODO(ang): gestire staccosa della creazione del livello tramite objectLoader??? 
        // serve che il level manager implementi un gestore per caricare i livelli???
        // e quindi questo diventi semplicemente un coso che sceglie randomicamente quale loader prendere???
    }

    Level::~Level() {
        for (unsigned int i = 0; i < levels_.size(); i++) {
            delete levels_[i];
        }
        delete levelIdx_;
        delete player_;
    }

    Player *Level::getPlayer() {
        return player_;
    }

    int Level::addLevel() {
        levels_.push_back(new level::Level(levelScreenSize_, levelIdx_->getCurrent()));
        return (int) levels_.size() - 1;
    }

    level::Collidable *Level::getCollision(Position pos) {
        return levels_[levelIdx_->getCurrent()]->getCollision(pos);
    }

    void Level::goToLevel(int levelIdx) {
        levels_[levelIdx_->getCurrent()]->setLastPlayerPosition(player_->getPosition());
        if (levelIdx < 0 || levelIdx >= (int) levels_.size()) {
            return;
        }
        levelIdx_->setCurrent(levelIdx);
        player_->setPosition(levels_[levelIdx_->getCurrent()]->getLastPlayerPosition());
        return;
    }

    void Level::render(WINDOW *win, bool force) {
        player_->clearLast(win);
        player_->render(win, force);

        if (levelIdx_->isChanged()) {
            force = true;
            // TODO(ang): clear screen
        }

        levels_[levelIdx_->getCurrent()]->render(win, force);
        // TODO(ang): print player ( valuta se è meglio printarlo qui o in level/level 
        // io pensavo fosse meglio il level/level (gio))
    }
}