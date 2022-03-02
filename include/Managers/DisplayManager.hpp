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
    //la windows che contine il gioco
    WINDOW *win=nullptr;
public:
    DisplayManager();
    //~DisplayManager();
    //crea la finestra e calcola il next frame
    void gameLoop(LevelManager* levelManager);
    //fa il display degli oggetti
    void nextFrame(LevelManager* levelManager);
    //crea la finestra di gioco
    void createWindow(LevelManager* levelManager);
    //distrugge la finestra di gioco
    void deleteWindow();

};