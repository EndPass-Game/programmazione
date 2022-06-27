#pragma once

#include <ncurses.h>

#include "display.hpp"
#include "input.hpp"
#include "level.hpp"

namespace manager {
    // TODO: spiegare delle necessità dei due thread e come collaborano insieme
    // dato che è un dettaglio implementativo e non di interfaccia spiegarlo nel file cpp

    // Singoletto: unica istanza di GameManager
    // Che deve gestire ad alto livello anche tutte le altre istanze
    // di managers, e si occupa di creare i due loop del gioco
    // in due thread
    class Game {
      private:
        Display *displayManager_;
        Input *inputManager_;
        Level *levelInstance_;

        // istanza del singleton
        static Game *instance_;

      public:
        Game();
        ~Game();

        //ritorna l'istanza del singoletto
        static Game *GetInstance();

        Level *getLevelManager() const;

        //Crea i thread e gestisce i menu prima e dopo il gioco
        void run();
    };
}