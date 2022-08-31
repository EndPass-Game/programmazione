#pragma once

#include "gamestruct/logger.hpp"
#include "manager/display.hpp"
#include "manager/input.hpp"
#include "manager/level.hpp"

namespace manager {
    class Game {
      private:
        ViewManager *viewManager_;
        Display *displayManager_;
        Input *inputManager_;

        Logger logger_;

      public:
        /**
         * @brief Inizializza il gioco
         */
        Game();

        /**
         * @brief Distruttore del gioco
         */
        ~Game();

        /**
         * @brief Crea i thread e gestisce i menu prima e dopo il gioco
         */
        void run();
    };
};  // namespace manager
