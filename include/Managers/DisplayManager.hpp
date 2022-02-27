/*
Descrizione:
Questa classe si occupa di mostrare sullo schermo

Funzioni:
1. Errori 
*/
#pragma once

#include <ncurses.h>
#include "LevelManager.hpp"

class DisplayManager {
private:
    WINDOW *win;
    LevelManager* levelManager;
public:
    DisplayManager();
    //~DisplayManager();
    void gameLoop();
    void setLevelManager(LevelManager* levelManager);
    void nextFrame();

    // methods to render something
    // Boxes
    // people
    // Writings ok?
};