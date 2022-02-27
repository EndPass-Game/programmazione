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
public:
    LevelManager* levelManager;
    DisplayManager();
    //~DisplayManager();
    void gameLoop();
    void nextFrame();

    // methods to render something
    // Boxes
    // people
    // Writings ok?
};