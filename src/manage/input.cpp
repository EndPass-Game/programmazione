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

namespace manager
{

    void Input::handleInputOnGameState(int input, Level *levelManager)
    {
        Player *player = levelManager->player;
        switch (input)
        {
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
            levelManager->gameState->setCurrent(enums::GameState::PAUSE);
            break;
        }
    }
    void Input::handleInputOnPauseState(int input, Level *levelManager)
    {
        switch (input)
        {
        case 'p':
            levelManager->gameState->setCurrent(enums::GameState::RUNNING);
            break;
        }
    }
    void Input::handleInputOnAllState(int input, Level *levelManager)
    {
        switch (input)
        {
        case 'q':
            levelManager->gameState->setCurrent(enums::GameState::FINISH);
            break;
        }
    }

    void Input::run(Level *levelManager)
    {
        timeout(300);
        while (levelManager->gameState->getCurrent() != enums::GameState::FINISH)
        {
            int current_input = getch();
            if (current_input != -1){

                switch (levelManager->gameState->getCurrent())
                {
                case enums::GameState::PAUSE:
                    handleInputOnPauseState(current_input,levelManager);
                    break;
                case enums::GameState::RUNNING:
                    handleInputOnGameState(current_input,levelManager);
                    break;
                }
                handleInputOnAllState(current_input, levelManager);
            }
        }
    }
}