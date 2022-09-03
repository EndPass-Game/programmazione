#include "loader/level-provider.hpp"

#include <iostream>

#include "loader/directory-loader.hpp"

namespace loader {

    LevelProvider &LevelProvider::getInstance() {
        /* Avere una variabile locale statica che rappresenta l'istanza univoca.
         * in quanto è statico, c'è solo un'istanza di questa variabile. È anche
         * inizializzato quando questa funzione viene chiamata.
         */
        static LevelProvider theInstance;
        return theInstance;
    }

    LevelProvider::LevelProvider(const char *directory)
        : hasLoadedLevels_(false),
          logger_("loader::LevelProvider") {
        DirectoryLoader loader(directory);
        datastruct::Vector<char *> fileNames = loader.getFileNames();
        for (unsigned int i = 0; i < fileNames.size(); i++) {
            loadedLevels_.push_back(new LoaderHandler(fileNames[i]));
        }
    }

    LevelProvider::~LevelProvider() {
        logger_.debug("deletion of static instance");
        for (unsigned int i = 0; i < loadedLevels_.size(); i++) {
            delete loadedLevels_[i];
        }
    }

    void LevelProvider::loadLevels() {
        if (hasLoadedLevels_) {
            logger_.error("Levels already loaded, the loading should only be called once");
            logger_.info("returning without loading anything");
            return;
        }

        logger_.info("Loading levels");
        hasLoadedLevels_ = true;

        for (unsigned int i = 0; i < loadedLevels_.size(); i++) {
            loadedLevels_[i]->load();
            _dispatchHandler(loadedLevels_[i]);
        }

        logger_.debug("Loaded %d levels", loadedLevels_.size());
    }

    level::Level *LevelProvider::getLevel(enums::Direction direction, Player *player, int levelIdx) {
        enums::Direction oppositeDirection = _getOppositeDirection(direction);
        datastruct::Vector<LoaderHandler *> *levelVector = _getLevelVector(oppositeDirection);
        logger_.debug("getting level with direction %d", oppositeDirection);

        if (levelVector->size() == 0) {
            logger_.warning(
                "No levels found for direction %d "
                " choosing from all available levels",
                oppositeDirection
            );
            levelVector = &loadedLevels_;
        }

        int random = rand() % levelVector->size();

        level::Level *level;
        if (levelIdx == -1) {
            level = new level::Level(levelVector->at(random), player);
        } else {
            level = new level::Level(levelVector->at(random), player, oppositeDirection, levelIdx);
        }

        // ricarica una nuova copia delle informazioni per essere consumata
        // alla prossima chiamata
        levelVector->at(random)->load();
        return level;
    }

    void LevelProvider::_dispatchHandler(LoaderHandler *handler) {
        if (handler->doorLoader.hasNorthDoor()) {
            withNorthDoor_.push_back(handler);
        }

        if (handler->doorLoader.hasEastDoor()) {
            withEastDoor_.push_back(handler);
        }

        if (handler->doorLoader.hasSouthDoor()) {
            withSouthDoor_.push_back(handler);
        }

        if (handler->doorLoader.hasWestDoor()) {
            withWestDoor_.push_back(handler);
        }
    }

    enums::Direction LevelProvider::_getOppositeDirection(enums::Direction direction) {
        enums::Direction oppositeDirection;
        switch (direction) {
            case enums::Direction::UP:
                oppositeDirection = enums::Direction::DOWN;
                break;
            case enums::Direction::DOWN:
                oppositeDirection = enums::Direction::UP;
                break;
            case enums::Direction::LEFT:
                oppositeDirection = enums::Direction::RIGHT;
                break;
            case enums::Direction::RIGHT:
                oppositeDirection = enums::Direction::LEFT;
                break;
            default:
                oppositeDirection = enums::Direction::NONE;
                break;
        }
        return oppositeDirection;
    }

    datastruct::Vector<LoaderHandler *> *LevelProvider::_getLevelVector(enums::Direction direction) {
        datastruct::Vector<LoaderHandler *> *levelVector;

        switch (direction) {
            case enums::Direction::UP:
                levelVector = &withNorthDoor_;
                break;
            case enums::Direction::DOWN:
                levelVector = &withSouthDoor_;
                break;
            case enums::Direction::LEFT:
                levelVector = &withWestDoor_;
                break;
            case enums::Direction::RIGHT:
                levelVector = &withEastDoor_;
                break;
            default:
                logger_.warning("_getLevelVector called with direction = NONE");
                levelVector = &loadedLevels_;
                break;
        }
        return levelVector;
    }

}  // namespace loader