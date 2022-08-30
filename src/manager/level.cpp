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

#include "entities/weapon/bullet.hpp"
#include "enums/direction.hpp"
#include "loader/level-provider.hpp"

namespace manager {

    Level::Level()
        : levels_(datastruct::Vector<level::Level *>()),
          logger_("manager::Level") {
        player_ = new Player();
        levelIdx_ = new StateWatcher<int>(-1);  // -1 indica che non è stato ancora caricato nessun livello
        logQueue_ = new LogQueue(manager::kLogAreaSize.colonna - 2, manager::kLogAreaSize.riga - 2, manager::kPaddingLogArea);

        int newLevelIdx = _addLevel();
        levelIdx_->setCurrent(newLevelIdx);
        player_->setPosition(levels_[newLevelIdx]->getLastPlayerPosition());
        goToLevel(newLevelIdx);
    }

    Level::~Level() {
        for (unsigned int i = 0; i < levels_.size(); i++) {
            delete levels_[i];
        }
        delete levelIdx_;
        delete player_;
        delete logQueue_;
    }

    Player *Level::getPlayer() {
        return player_;
    }

    int Level::_addLevel(enums::Direction direction) {
        logger_.info("Adding new level");

        loader::LevelProvider &levelProvider = loader::LevelProvider::getInstance();

        if (levelIdx_->getCurrent() == -1) {
            levels_.push_back(levelProvider.getLevel(direction));
        } else {
            levels_.push_back(levelProvider.getLevel(direction, levelIdx_->getCurrent()));
        }

        return (int) levels_.size() - 1;
    }

    level::Collidable *Level::getCollision(Position pos) {
        return levels_[levelIdx_->getCurrent()]->getCollision(pos);
    }

    void Level::playerShoot() {
        if (!player_->canFire()) {
            return;
        }

        player_->resetCoolDown();
        logger_.info("player firing a bullet");
        Position bulletPosition = player_->getNextPosition();
        logger_.debug("next position: %d, %d", bulletPosition.colonna, bulletPosition.riga);
        logger_.debug("curr position: %d, %d", player_->getPosition().colonna, player_->getPosition().riga);
        level::Collidable *collision = getCollision(bulletPosition);

        // BUG: a volte quando il player va troppo veloce, prendere la sua prossima
        // posizione non è ancora sufficiente per non cancellarlo dallo schermo

        // TODO(simo): check per vedere la collisione istantanea, cioè gestisci questo
        // caso ad esempio fare danno subito, perché il bullet va a controllare se
        // la cella in cui vuole andare colpisce qualcosa
        if (collision == nullptr) {
            weapon::Bullet *bullet = new weapon::Bullet(bulletPosition, player_->getLastNotNullDirection());
            levels_[levelIdx_->getCurrent()]->addBullet(bullet);
        }
    }

    void Level::goToLevel(int levelIdx) {
        logger_.info("Loading level with index: %d", levelIdx);

        if (levelIdx < 0 || levelIdx >= (int) levels_.size()) {
            logger_.error("Invalid go-to-level index, maximum index is: %u", levels_.size());
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
            levelIdx_->setCurrent(levelIdx_->getCurrent());  // FIX PG-34
        }

        levels_[levelIdx_->getCurrent()]->enemiesAttack(win, this);
        levels_[levelIdx_->getCurrent()]->renderEnemies(win, this);

        // WARNING: non spostare questo render sotto al player,
        // vogliamo che prima renderizzi i bullets e poi il player
        // altrimenti rischiamo che il bullet cancelli il player.
        levels_[levelIdx_->getCurrent()]->render(win, force, this);

        player_->move(this);
        player_->clearLast(win);
        player_->render(win, force);
        player_->coolDown();

        // TODO(ang): print player ( valuta se è meglio printarlo qui o in level/level
        // io pensavo fosse meglio il level/level (gio))
    }

    LogQueue *Level::getLogQueue() {
        return logQueue_;
    }

    level::Level *Level::getLevel() {
        return levels_[levelIdx_->getCurrent()];
    }

    void Level::generateLevel(level::DoorSegment *door) {
        if (!door->isOpen()) {
            return;
        }
        int nextLevelIdx = _addLevel(door->getFacingDir());
        door->setNextLevelIdx(nextLevelIdx);
    }
}  // namespace manager
