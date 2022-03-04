/*
*  Descrizione:
*  Questa classe gestisce tutti gli input del gioco
*  e chiama le funzioni corrette a seconda dell'input 
*  
*
*/
#include <ncurses.h>

#include "game_state.hpp"
#include "input.hpp"
#include "level.hpp"
#include "player.hpp"

namespace manager {

    Input::Input() {

    }

    void Input::run(Level* levelManager){
        timeout(300);
        Player* player = levelManager->player;
        while(levelManager->gameState != enums::GameState::FINISH){
            // TODO: mettere direction del player privata (ed encapsulata)
            // e aggiungere getter e setter
            int current_input = getch();
            if(current_input == -1)continue;
            switch(current_input) {
            case 'a':
                player->setDirection(enums::Direction::LEFT);
                break;
            case 'd':
                player->setDirection(enums::Direction::RIGHT);
                break;
            case 's':
                player->setDirection(enums::Direction::DOWN);
                break;
            case 'w':
                player->setDirection(enums::Direction::UP);
                break;
            case 'p':
                levelManager->gameState = enums::GameState::PAUSE;
                break;
            case 'q':
                levelManager->gameState = enums::GameState::FINISH;
                break;

            // TODO: un defult case? serve?
            }
        }
    }   
}