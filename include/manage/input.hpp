/*
*  Descrizione:
*  Questa classe gestisce tutti gli input del gioco
*  e chiama le funzioni corrette a seconda dell'input 
*  
*/
#pragma once

#include "level.hpp"

namespace manager {
    class Input {
      private:
        void handleInputOnGameState(int input); 
        void handleInputOnPauseState(int input); 
        void handleInputOnAllState(int input);

      public:
        Input();
        void run();
    };
}