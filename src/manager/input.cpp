/*
*  Descrizione:
*  Questa classe gestisce tutti gli input del gioco
*  e chiama le funzioni corrette a seconda dell'input 
*  
*
*/
#include "manager/input.hpp"

#include <ncurses.h>

#include "enums/game_state.hpp"
#include "entities/player.hpp"
#include "manager/game.hpp"
#include "manager/level.hpp"

namespace manager
{
    Input::Input() {}
    void Input::handleInputOnGameState(int input)
    {
        Level *levelManager = Game::GetInstance()->getLevelManager();
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
    void Input::handleInputOnPauseState(int input)
    {
        Level *levelManager = Game::GetInstance()->getLevelManager();
        switch (input)
        {
        case 'p':
            levelManager->gameState->setCurrent(enums::GameState::RUNNING);
            break;
        }
    }
    void Input::handleInputOnAllState(int input)
    {
        Level *levelManager = Game::GetInstance()->getLevelManager();
        switch (input)
        {
        case 'q':
            levelManager->gameState->setCurrent(enums::GameState::FINISH);
            break;
        }
    }

    void Input::run()
    {
        Level *levelManager = Game::GetInstance()->getLevelManager();
        timeout(300);
        while (levelManager->gameState->getCurrent() != enums::GameState::FINISH)
        {
            int current_input = getch();
            if (current_input != -1){
                switch (levelManager->gameState->getCurrent())
                {
                case enums::GameState::PAUSE:
                    handleInputOnPauseState(current_input);
                    break;
                case enums::GameState::RUNNING:
                    handleInputOnGameState(current_input);
                    break;
                }
                handleInputOnAllState(current_input);
            }
        }
    }
}