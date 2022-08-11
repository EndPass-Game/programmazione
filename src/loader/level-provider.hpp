#pragma once

#include "datastruct/vector.hpp"
#include "enums/direction.hpp"
#include "gamestruct/logger.hpp"
#include "level/level.hpp"
#include "loader/loader-handler.hpp"

namespace loader {
    class LevelProvider {
      private:
        LevelProvider(const char *directory = "assets/");
        datastruct::Vector<LoaderHandler *> loadedLevels_;

        Logger logger_;

      public:
        // @retuns l'istanza singleton
        static LevelProvider &getInstance();

        static void init(const char *directory = "assets/");

        LevelProvider(const LevelProvider &other) = delete;
        LevelProvider &operator=(const LevelProvider &other) = delete;

        ~LevelProvider();

        // Carica tutti i livelli
        // è utile per verificare se un livello è malformato all'inizio del gioco
        void loadLevels();

        // @param levelIdx l'indice del livello di arrivo, -1 default per dire che non c'è nessun livello
        // @returns un livello con una porta nella direzione desiderata
        level::Level *getLevel(enums::Direction wantedDirection, int levelIdx = -1);
    };
}  // namespace loader
