#pragma once

#include "manager/level.hpp"
#include "manager/view-manager.hpp"

/**
 *  @brief Questa classe gestisce tutti gli input del gioco
 *  e chiama le funzioni corrette a seconda dell'input
 */
namespace manager {
    class Input {
      private:
        ViewManager *viewManager;

      public:
        Input(ViewManager *viewManager);

        /**
         * @brief funzione che viene eseguita finché rimangono elementi nel viewmanager
         * prende gli input e li passa alla view corrente
         */
        void run();
    };
}  // namespace manager
