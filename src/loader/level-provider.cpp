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

    LevelProvider::LevelProvider(const char *directory) : logger_("loader::LevelProvider") {
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
        logger_.info("Loading levels");

        for (unsigned int i = 0; i < loadedLevels_.size(); i++) {
            loadedLevels_[i]->load();
        }

        logger_.debug("Loaded %d levels", loadedLevels_.size());
    }

    level::Level *LevelProvider::getLevel(enums::Direction wantedDirection, int levelIdx) {
        // TODO(ang): il random è solamente temporaneo 
        int random = rand() % loadedLevels_.size();

        level::Level *level; 
        if (levelIdx == -1) {
            level = new level::Level(loadedLevels_[random]);
        } else {
            level = new level::Level(loadedLevels_[random], levelIdx);
        }

        // ricarica una nuova copia delle informazioni per essere consumata
        // alla prossima chiamata
        loadedLevels_[random]->load(); 

        // TODO: utilizzare la direzione voluta per scegliere il livello 
        // Level *level = new Level();
        // level->setWantedDirection(wantedDirection);
        // level->setWallSegment(fileNames_[rand() % fileNames_.size()].wallLoader);
        // level->setDoorSegment(fileNames_[rand() % fileNames_.size()].doorLoader);
        // level->setPlayerPosition(fileNames_[rand() % fileNames_.size()].playerPosLoader);
        // level->setArtifact(fileNames_[rand() % fileNames_.size()].artifactLoader);
        // level->setPower(fileNames_[rand() % fileNames_.size()].powerLoader);
        return level;
    }

} // namespace loader