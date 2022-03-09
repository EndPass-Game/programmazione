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

        void handleInputOnGameState(int input,Level* levelManager); 
        void handleInputOnPauseState(int input,Level* levelManager); 
        void handleInputOnAllState(int input,Level* levelManager);
      public:
        //Input();
        //~InputManager();

        // ISSUE: perché questa funzione prende level manager se lo
        // ho già come membro privato?
        void run(Level* levelManager);
    };
}