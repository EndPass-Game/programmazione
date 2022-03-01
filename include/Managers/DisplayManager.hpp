/*
Descrizione:
Questa classe si occupa di mostrare sullo schermo

Funzioni:
1. Errori 
*/
#pragma once

#include <ncurses.h>
#include "LevelManager.hpp"
#include <thread>
#include <chrono>


class DisplayManager {
private:
    WINDOW *win;
    LevelManager* levelManager;
public:
    DisplayManager();
    //~DisplayManager();
    void gameLoop(LevelManager* levelManager);
    void nextFrame(LevelManager* levelManager);

    // methods to render something
    // Boxes
    // people
    // Writings ok?
};