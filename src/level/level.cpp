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
          entities_(),
          artifacts_(),
          powers_(),
          playerPositions_() {
        wallSegments_ = loader->wallLoader.getLoadedObjects();
        for (unsigned int i = 0; i < wallSegments_.size(); i++) {
            segment_.push_back((DisplayableSegment *) &wallSegments_[i]);
        }

        doorSegments_ = loader->doorLoader.getLoadedObjects();
        for (unsigned int i = 0; i < doorSegments_.size(); i++) {
            segment_.push_back((DisplayableSegment *) &doorSegments_[i]);
        }

        // avremmo una invalid-read se playerPositions_.size() == 0, ma questo non dovrebbe mai
        // succedere per checks in loader::LoaderHandler (in particolare quello sulle porte)
        playerPositions_ = loader->doorLoader.getPlayerPositions();
        lastPlayerPosition_ = playerPositions_.at(0);

        datastruct::Vector<collectables::Artifact> artifacts_ = loader->artifactLoader.getLoadedObjects();
        datastruct::Vector<collectables::Power> powers_ = loader->powerLoader.getLoadedObjects();
    }

    Level::Level(loader::LoaderHandler *loader, enums::Direction direction, int oldLevelIdx)
        : Level(loader) {
        logger_.debug("creating level pointing to leveldIdx: %d", oldLevelIdx);

        DoorSegment *chosenDoor = nullptr;
        unsigned int doorOffset = segment_.size() - doorSegments_.size();

        // questa parte assume che le porte siano tutte nell'ultima parte del segmento:
        for (unsigned int i = doorOffset; i < segment_.size(); i++) {
            DoorSegment *door = (DoorSegment *) segment_.at(i);
            if (door->getFacingDir() == direction) {
                chosenDoor = door;
                lastPlayerPosition_ = playerPositions_[i - doorOffset];
                break;
            }
        }

        if (chosenDoor == nullptr) {
            logger_.warning("no door found for direction %d", direction);
            logger_.info("choosing random door");
            int doorNumber = rand() % doorSegments_.size();
            chosenDoor = (DoorSegment *) segment_.at(doorOffset + doorNumber);
            lastPlayerPosition_ = playerPositions_[doorNumber];
        }

        chosenDoor->setNextLevelIdx(oldLevelIdx);
        chosenDoor->openDoor();
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
                logger_.debug("collided with segment %d", i);
                return (Collidable *) segment_[i];
            }
        }
        for (unsigned int i = 0; i < artifacts_.size(); i++) {
            if (artifacts_[i].getPosition() == pos) {
                collectables::Artifact *c = &artifacts_[i];
                artifacts_.remove(i);
                return (Collidable *) c;
            }
        }
        for (unsigned int i = 0; i < powers_.size(); i++) {
            if (powers_[i].getPosition() == pos) {
                collectables::Power *c = &powers_[i];
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
            artifacts_[i].render(win, force);
        }
        for (unsigned int i = 0; i < powers_.size(); i++) {
            powers_[i].render(win, force);
        }

        // TODO(ang): come fare a spostare gli entità?
        // 1. deve updatare questo oppure lo fa un render in un altro momento????
    }

    void Level::clear(WINDOW *win) {
        for (unsigned int i = 0; i < segment_.size(); i++) {
            segment_[i]->clear(win);
        }
        for (unsigned int i = 0; i < artifacts_.size(); i++) {
            artifacts_[i].clear(win);
        }
        for (unsigned int i = 0; i < powers_.size(); i++) {
            powers_[i].clear(win);
        }
    }
};  // namespace level