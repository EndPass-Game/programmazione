#include "level/level.hpp"

#include "collectables/power.hpp"
#include "datastruct/vector.hpp"
#include "entities/player.hpp"
#include "enums/collision-type.hpp"
#include "gamestruct/size.hpp"
#include "level/door-segment.hpp"
#include "level/wall-segment.hpp"
#include "manager/level.hpp"

namespace level {
    Level::Level(loader::LoaderHandler *loader)
        : lastPlayerPosition_(1, 1),
          segment_(),
          artifacts_(),
          powers_(),
          entities_(),
          playerPositions_(),
          numOfDoors_(0) {
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
    }

    Level::Level(loader::LoaderHandler *loader, enums::Direction direction, int oldLevelIdx)
        : Level(loader) {
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
        chosenDoor->openDoor();
    }

    Level::~Level() {
        for (unsigned int i = 0; i < segment_.size(); i++) {
            delete segment_[i];
        }

        for (unsigned int i = 0; i < entities_.size(); i++) {
            delete entities_[i];
        }

        for (unsigned int i = 0; i < artifacts_.size(); i++) {
            delete artifacts_[i];
        }

        for (unsigned int i = 0; i < powers_.size(); i++) {
            delete powers_[i];
        }
    }

    Position Level::getLastPlayerPosition() {
        return lastPlayerPosition_;
    }

    void Level::setLastPlayerPosition(Position pos) {
        lastPlayerPosition_ = pos;
    }

    bool Level::isPositionEmpty(Position pos) {
        return getCollision(pos) == nullptr;
    }

    Collidable *Level::getCollision(Position pos) {
        for (unsigned int i = 0; i < segment_.size(); i++) {
            if (segment_[i]->isPositionInSegment(pos)) {
                return (Collidable *) segment_[i];
            }
        }
        for (unsigned int i = 0; i < artifacts_.size(); i++) {
            if (artifacts_[i]->getPosition() == pos) {
                collectables::Artifact *c = artifacts_[i];
                artifacts_.remove(i);
                return (Collidable *) c;
            }
        }
        for (unsigned int i = 0; i < powers_.size(); i++) {
            if (powers_[i]->getPosition() == pos) {
                collectables::Power *c = powers_[i];
                powers_.remove(i);
                return (Collidable *) c;
            }
        }

        // TODO(simo): gestire altri oggetti di collisione
        // es: entity, ...
        return nullptr;
    }

    void Level::render(WINDOW *win, bool force) {
        for (unsigned int i = 0; i < segment_.size(); i++) {
            segment_[i]->render(win, force);
        }

        for (unsigned int i = 0; i < artifacts_.size(); i++) {
            artifacts_[i]->render(win, force);
        }
        for (unsigned int i = 0; i < powers_.size(); i++) {
            powers_[i]->render(win, force);
        }

        // TODO(ang): come fare a spostare gli entità?
        // 1. deve updatare questo oppure lo fa un render in un altro momento????
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
    }
};  // namespace level