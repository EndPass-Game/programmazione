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
    Player* player=levelManager->player;
    while(levelManager->gameState==GameState::RUNNING){
        int current_input=getch();
        if(current_input==-1)continue;
        switch(current_input){
        case 'a':
            player->direction=Direction::LEFT;
            break;
        case 'd':
            player->direction=Direction::RIGHT;
            break;
        case 's':
            player->direction=Direction::DOWN;
            break;
        case 'w':
            player->direction=Direction::UP;
            break;
        case 'p':
            levelManager->gameState=GameState::PAUSE;
            break;
        case 'q':
            levelManager->gameState=GameState::FINISH;
            break;
        }
    }
}