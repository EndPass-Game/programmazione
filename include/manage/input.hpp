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
      public:
        //Input();
        //~InputManager();
        void gameState(int input,Level* levelManager); 
        void pauseState(int input,Level* levelManager); 
        void allState(int input,Level* levelManager);

        // ISSUE: perché questa funzione prende level manager se lo
        // ho già come membro privato?
        void run(Level* levelManager);
    };
}