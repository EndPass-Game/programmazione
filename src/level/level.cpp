#include "level/level.hpp"

#include "datastruct/vector.hpp"
#include "gamestruct/size.hpp"
#include "entities/player.hpp"
#include "enums/direction.hpp"
#include "level/door-segment.hpp"
#include "level/wall-segment.hpp"
#include "enums/collision-type.hpp"
#include "manager/level.hpp"
#include "collectables/power.hpp"

namespace level {
    Level::Level(loader::LoaderHandler *loader) {
        segment_ = datastruct::Vector<DisplayableSegment *>();
        artifacts_ = datastruct::Vector<Artifact *>();
        entities_ = datastruct::Vector<Entity *>(0);
        powers_ = datastruct::Vector<Power *>();

        datastruct::Vector<WallSegment *> *segments = nullptr;
        segments = loader->wallLoader->getLoadedObjects();
        if (segments != nullptr) {
            for (unsigned int i = 0; i < segments->size(); i++) {
                segment_.push_back((DisplayableSegment *) segments->at(i));
            }
            delete segments;
        }

        datastruct::Vector<DoorSegment *> *doors = nullptr;
        doors = loader->doorLoader->getLoadedObjects();
        if (doors != nullptr) {
            numOfDoors_ = doors->size();
            for (unsigned int i = 0; i < doors->size(); i++) {
                segment_.push_back((DisplayableSegment *) doors->at(i));
            }
            delete doors;
        } else {
            numOfDoors_ = 0;
        }

        datastruct::Vector<Position *> *playersPos = nullptr;
        playersPos = loader->playerPosLoader->getLoadedObjects();
        if (playersPos != nullptr) {
            lastPlayerPosition_ = *playersPos->at(0); // only one player position is loaded
            for (unsigned int i = 0; i < playersPos->size(); i++) {
                delete playersPos->at(i);
            }
            delete playersPos;
        }

        datastruct::Vector<Artifact *> *artifacts = nullptr;
        artifacts = loader->artifactLoader->getLoadedObjects();
        if (artifacts != nullptr) {
            for (unsigned int i = 0; i < artifacts->size(); i++) {
                artifacts_.push_back(artifacts->at(i));
                }
            delete artifacts;
        }

        datastruct::Vector<Power *> *powers = nullptr;
        powers = loader->powerLoader->getLoadedObjects();
        if (powers != nullptr) {
            for (unsigned int i = 0; i < powers->size(); i++) {
                powers_.push_back(powers->at(i));
            }
            delete powers;
        }
    }

    Level::Level(loader::LoaderHandler *loader, int oldLevelIdx): Level(loader) {
        int doorNumber = rand() % numOfDoors_;
        // questa parte assume che le porte siano tutte nell'ultima parte del segmento: 
        DoorSegment *chosenDoor = (DoorSegment *) segment_.at(segment_.size() - numOfDoors_ + doorNumber); 
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

        for (unsigned int i = 0; i < powers_.size(); i++){
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
        for (unsigned int i = 0; i < artifacts_.size(); i++){
            if(artifacts_[i]->getPosition() == pos){
                Artifact *c = artifacts_[i];
                artifacts_.remove(i);
                return (Collidable *) c;
            }
        }
        for (unsigned int i = 0; i<powers_.size(); i++){
            if(powers_[i]->getPosition() == pos){
                Power *c = powers_[i];
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
}; // namespace level