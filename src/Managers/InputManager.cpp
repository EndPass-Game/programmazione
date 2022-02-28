/*
*  Descrizione:
*  Questa classe gestisce tutti gli input del gioco
*  e chiama le funzioni corrette a seconda dell'input 
*  
*
*/
#include "InputManager.hpp"

InputManager::InputManager(){

}


void InputManager::runInputManager(LevelManager* levelManager){
	timeout(300);
    while(!levelManager->isRunning){
        int current_input=getch();
        if(current_input==-1)continue;
        char char_value=(char)current_input;
        switch (char_value)
        {
        case KEY_LEFT:

            break;
        case KEY_RIGHT:

            break;
        case KEY_DOWN:

            break;
        case KEY_UP:

            break;
        case 'p':
            break;
        case 'q':
            break;
        default:
            break;
        }
    }
}