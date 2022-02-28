/*
*  Descrizione:
*  Questa classe gestisce tutti gli input del gioco
*  e chiama le funzioni corrette a seconda dell'input 
*  
*/
#pragma once

#include "LevelManager.hpp"
#include <ncurses.h>

class InputManager {
private:
    LevelManager* levelManager;
public:
    InputManager();
    //~InputManager();
    void runInputManager(LevelManager* levelManager);
};