#pragma once

#include "datastruct/vector.hpp"
#include "entities/player.hpp"
#include "enums/direction.hpp"
#include "gamestruct/logger.hpp"
#include "level/level.hpp"
#include "loader/loader-handler.hpp"

namespace loader {
    class LevelProvider {
      private:
        LevelProvider(const char *directory = "assets/");
        datastruct::Vector<LoaderHandler *> loadedLevels_;
        datastruct::Vector<LoaderHandler *> withNorthDoor_;
        datastruct::Vector<LoaderHandler *> withEastDoor_;
        datastruct::Vector<LoaderHandler *> withSouthDoor_;
        datastruct::Vector<LoaderHandler *> withWestDoor_;

        bool hasLoadedLevels_;

        Logger logger_;

        enums::Direction _getOppositeDirection(enums::Direction direction);
        void _dispatchHandler(LoaderHandler *handler);
        datastruct::Vector<LoaderHandler *> *_getLevelVector(enums::Direction direction);

      public:
        // @returns l'istanza singleton
        static LevelProvider &getInstance();

        LevelProvider(const LevelProvider &other) = delete;
        LevelProvider &operator=(const LevelProvider &other) = delete;

        ~LevelProvider();

        // Carica tutti i livelli
        // è utile per verificare se un livello è malformato all'inizio del gioco
        void loadLevels();

        // @param levelIdx l'indice del livello di arrivo, -1 default per dire che non c'è nessun livello
        // @returns un livello con una porta nella direzione desiderata
        level::Level *getLevel(enums::Direction wantedDirection, Player *player, int levelIdx = -1);
    };
}  // namespace loader
