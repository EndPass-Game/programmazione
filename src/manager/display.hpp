#pragma once

#include <chrono>
#include <ncurses.h>
#include <thread>

#include "gamestruct/logger.hpp"
#include "gamestruct/size.hpp"
#include "gamestruct/state-watcher.tpp"
#include "manager/view-manager.hpp"

namespace manager {
    class Display {
      private:
        ViewManager *viewManager;
        StateWatcher<Size> screenSize;
        Size getScreenSize();
        Logger logger_;

        bool checkUpdateView();
        void updateScreenSize();

      public:
        Display(ViewManager *viewManager);

        /**
         * @brief funzione che viene eseguita finché non ci sono più view nello stack
         */
        void gameLoop();
    };
}  // namespace manager