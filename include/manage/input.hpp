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
        Level* levelManager_; // FIXME: perché qui c'è un level manager ma non lo uso
      public:
        Input();
        //~InputManager();

        // ISSUE: perché questa funzione prende level manager se lo
        // ho già come membro privato?
        void run(Level* levelManager);
    };
}