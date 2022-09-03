#include "level/level.hpp"

#include "collectables/power.hpp"
#include "datastruct/vector.tpp"
#include "entities/enemy.hpp"
#include "entities/entity.hpp"
#include "entities/player.hpp"
#include "enums/collision-type.hpp"
#include "gamestruct/size.hpp"
#include "level/collidable.hpp"
#include "level/door-segment.hpp"
#include "level/wall-segment.hpp"
#include "manager/level.hpp"

namespace level {
    Level::Level(loader::LoaderHandler *loader, Player *player)
        : lastPlayerPosition_(1, 1),
          player_(player),
          segment_(),
          artifacts_(),
          powers_(),
          enemies_(),
          bullets_(),
          playerPositions_(),
          numOfDoors_(0),
          logger_("level::Level") {
        datastruct::Vector<WallSegment *> *segments = nullptr;
        segments = loader->wallLoader.getLoadedObjects();
        if (segments != nullptr) {
            for (unsigned int i = 0; i < segments->size(); i++) {
                segment_.push_back((DisplayableSegment *) segments->at(i));
            }
        }

        datastruct::Vector<DoorSegment *> *doors = nullptr;
        doors = loader->doorLoader.getLoadedObjects();
        if (doors != nullptr) {
            numOfDoors_ = doors->size();
            for (unsigned int i = 0; i < doors->size(); i++) {
                segment_.push_back((DisplayableSegment *) doors->at(i));
            }
        }

        // avremmo una invalid-read se playerPositions_.size() == 0, ma questo non dovrebbe mai
        // succedere per checks in loader::LoaderHandler (in particolare quello sulle porte)
        playerPositions_ = loader->doorLoader.getPlayerPositions();
        lastPlayerPosition_ = playerPositions_.at(0);

        datastruct::Vector<LocalDoor *> *localDoors = nullptr;
        localDoors = loader->localDoorLoader.getLoadedObjects();
        if (localDoors != nullptr) {
            for (unsigned int i = 0; i < localDoors->size(); i++) {
                localDoors_.push_back(localDoors->at(i));
            }
        }

        datastruct::Vector<collectables::Artifact *> *artifacts = nullptr;
        artifacts = loader->artifactLoader.getLoadedObjects();
        if (artifacts != nullptr) {
            for (unsigned int i = 0; i < artifacts->size(); i++) {
                artifacts_.push_back(artifacts->at(i));
            }
        }

        datastruct::Vector<collectables::Power *> *powers = nullptr;
        powers = loader->powerLoader.getLoadedObjects();
        if (powers != nullptr) {
            for (unsigned int i = 0; i < powers->size(); i++) {
                powers_.push_back(powers->at(i));
            }
        }

        datastruct::Vector<entities::Enemy *> *enemies = nullptr;
        enemies = loader->enemyLoader.getLoadedObjects();
        if (enemies != nullptr) {
            for (unsigned int i = 0; i < enemies->size(); i++) {
                enemies_.push_back(enemies->at(i));
            }
        }
    }

    Level::Level(loader::LoaderHandler *loader, Player *player, enums::Direction direction, int oldLevelIdx)
        : Level(loader, player) {
        logger_.debug("creating level pointing to leveldIdx: %d", oldLevelIdx);

        DoorSegment *chosenDoor = nullptr;

        // questa parte assume che le porte siano tutte nell'ultima parte del segmento:
        for (unsigned int i = segment_.size() - numOfDoors_; i < segment_.size(); i++) {
            DoorSegment *door = (DoorSegment *) segment_.at(i);
            if (door->getFacingDir() == direction) {
                chosenDoor = door;
                lastPlayerPosition_ = playerPositions_[i - (segment_.size() - numOfDoors_)];
                break;
            }
        }

        if (chosenDoor == nullptr) {
            logger_.warning("no door found for direction %d", direction);
            logger_.info("choosing random door");
            int doorNumber = rand() % numOfDoors_;
            chosenDoor = (DoorSegment *) segment_.at(segment_.size() - numOfDoors_ + doorNumber);
            lastPlayerPosition_ = playerPositions_[doorNumber];
        }

        chosenDoor->setNextLevelIdx(oldLevelIdx);
        chosenDoor->open();
    }

    Level::~Level() {
        for (unsigned int i = 0; i < segment_.size(); i++) {
            delete segment_[i];
        }

        for (unsigned int i = 0; i < enemies_.size(); i++) {
            delete enemies_[i];
        }

        for (unsigned int i = 0; i < artifacts_.size(); i++) {
            delete artifacts_[i];
        }

        for (unsigned int i = 0; i < powers_.size(); i++) {
            delete powers_[i];
        }

        for (unsigned int i = 0; i < bullets_.size(); i++) {
            delete bullets_[i];
        }

        for (unsigned int i = 0; i < localDoors_.size(); i++) {
            delete localDoors_[i];
        }
    }

    Position Level::getLastPlayerPosition() {
        return lastPlayerPosition_;
    }

    void Level::setLastPlayerPosition(Position pos) {
        lastPlayerPosition_ = pos;
    }

    Collidable *Level::getCollision(Position pos) const {
        for (unsigned int i = 0; i < segment_.size(); i++) {
            if (segment_[i]->isPositionInSegment(pos)) {
                return (Collidable *) segment_[i];
            }
        }

        for (unsigned int i = 0; i < localDoors_.size(); i++) {
            if (localDoors_[i]->isPositionInSegment(pos)) {
                return (Collidable *) localDoors_[i];
            }
        }

        for (unsigned int i = 0; i < artifacts_.size(); i++) {
            if (artifacts_[i]->getPosition() == pos) {
                collectables::Artifact *c = artifacts_[i];
                return (Collidable *) c;
            }
        }

        for (unsigned int i = 0; i < powers_.size(); i++) {
            if (powers_[i]->getPosition() == pos) {
                collectables::Power *c = powers_[i];
                return (Collidable *) c;
            }
        }

        for (unsigned int i = 0; i < enemies_.size(); i++) {
            if (enemies_[i]->getPosition() == pos) {
                entities::Enemy *c = enemies_[i];
                return (Collidable *) c;
            }
        }

        if (player_->getPosition() == pos) {
            return (Collidable *) player_;
        }

        return nullptr;
    }

    void Level::addBullet(weapon::Bullet *bullet) {
        bullets_.push_back(bullet);
    }

    void Level::deleteCollidable(Collidable *collidable) {
        enums::CollisionType type = collidable->getCollisionType();
        switch (type) {
            case enums::CollisionType::ARTIFACT:
                artifacts_.remove(artifacts_.indexOf((collectables::Artifact *) collidable));
                delete (collectables::Artifact *) collidable;
                break;
            case enums::CollisionType::POWER:
                powers_.remove(powers_.indexOf((collectables::Power *) collidable));
                delete (collectables::Power *) collidable;
                break;
            // supponendo che gli entity da eliminare siano sempre e solo gli enemies
            case enums::CollisionType::ENTITY:
                enemies_.remove(enemies_.indexOf((entities::Enemy *) collidable));
                delete (entities::Enemy *) collidable;
                break;
            default:
                logger_.warning("deleteCollidable: type is not supported, not deleted");
                break;
        }
    }

    void Level::render(WINDOW *win, bool force, manager::Level *levelManager) {
        player_->render(win, force);

        for (unsigned int i = 0; i < enemies_.size(); i++) {
            enemies_[i]->render(win, force);

            if (enemies_[i]->isDead()) {
                enemies_[i]->clear(win);
                delete enemies_[i];
                enemies_.remove(i);

                if (this->isComplete()) {
                    this->openAllDoors();
                }
            }
        }

        for (unsigned int i = 0; i < segment_.size(); i++) {
            segment_[i]->render(win, force);
        }

        for (unsigned int i = 0; i < artifacts_.size(); i++) {
            artifacts_[i]->render(win, force);
        }

        for (unsigned int i = 0; i < powers_.size(); i++) {
            powers_[i]->render(win, force);
        }

        unsigned int bulletIdx = 0;
        while (bulletIdx < bullets_.size()) {
            if (bullets_[bulletIdx]->isDestroyed()) {
                bullets_[bulletIdx]->clear(win);
                delete bullets_[bulletIdx];
                bullets_.remove(bulletIdx);
            } else {
                bullets_[bulletIdx]->clearLast(win);
                bullets_[bulletIdx]->render(win, force);
                bulletIdx++;
            }
        }

        for (unsigned int i = 0; i < localDoors_.size(); i++) {
            localDoors_[i]->render(win, force);
        }
    }

    void Level::clear(WINDOW *win) {
        for (unsigned int i = 0; i < segment_.size(); i++) {
            segment_[i]->clear(win);
        }

        for (unsigned int i = 0; i < artifacts_.size(); i++) {
            artifacts_[i]->clear(win);
        }

        for (unsigned int i = 0; i < powers_.size(); i++) {
            powers_[i]->clear(win);
        }

        for (unsigned int i = 0; i < bullets_.size(); i++) {
            // TODO: possibile bug che il proiettile resti bloccato nel punto in cui
            // abbiamo lasciato il livello?? è un bug??
            bullets_[i]->clear(win);
        }

        for (unsigned int i = 0; i < enemies_.size(); i++) {
            enemies_[i]->clear(win);
        }
        player_->clear(win);

        for (unsigned int i = 0; i < localDoors_.size(); i++) {
            localDoors_[i]->clear(win);
        }
    }

    void Level::act(manager::Level *levelManager) {
        for (unsigned int i = 0; i < enemies_.size(); i++) {
            enemies_[i]->act(levelManager);
        }

        for (unsigned int i = 0; i < bullets_.size(); i++) {
            bullets_[i]->act(levelManager);
        }

        player_->act(levelManager);
    }

    bool Level::isComplete() {
        logger_.debug("size of enemies is %d and of artifacts %d", enemies_.size(), artifacts_.size());
        logger_.debug("value of the boolean is %d", enemies_.size() == 0 && artifacts_.size() == 0);
        return enemies_.size() == 0 && artifacts_.size() == 0;
    }

    void Level::openLocalDoor(int id) {
        for (unsigned int i = 0; i < localDoors_.size(); i++) {
            if (localDoors_[i]->getId() == id) {
                localDoors_[i]->open();
            }
        }
    }

    void Level::openAllDoors() {
        logger_.info("All doors are open");
        // si assume che le porte siano nell'ultima parte del segmento
        for (unsigned int i = segment_.size() - numOfDoors_; i < segment_.size(); i++) {
            dynamic_cast<DoorSegment *>(segment_[i])->open();
        }
    }
};  // namespace level