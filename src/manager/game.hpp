#pragma once

#include "manager/display.hpp"
#include "manager/input.hpp"
#include "manager/level.hpp"
#include "gamestruct/logger.hpp"

namespace manager {
    class Game{
      private:
        ViewManager *viewManager_;
        Display *displayManager_;
        Input *inputManager_;
        Logger logger_ = Logger("MAIN GAME");
        
      public:
        Game();
        ~Game();

        // Crea i thread e gestisce i menu prima e dopo il gioco
        void run();
    };
}; // namespace manager