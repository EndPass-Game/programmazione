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
        //fa l'handle degli input che il programma prende se è nello stato Running
        void gameState(int input,Level* levelManager); 
        //fa l'handle degli input che il programma prende se è nello stato di pausa
        void pauseState(int input,Level* levelManager); 
        //fa l'handle degli input che il programma prende in qualsiasi stato
        void allState(int input,Level* levelManager);

        // ISSUE: perché questa funzione prende level manager se lo
        // ho già come membro privato?
        void run(Level* levelManager);
    };
}