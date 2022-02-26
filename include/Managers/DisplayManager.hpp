/*
Descrizione:
Questa classe si occupa di mostrare sullo schermo

Funzioni:
1. Errori 
*/
#pragma once

#include <ncurses.h>

class DisplayManager {
private:
    WINDOW *win;
public:
    DisplayManager();
    ~DisplayManager();

    int nextFrame();

    // methods to render something
    // Boxes
    // people
    // Writings ok?
};