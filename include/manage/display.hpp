/*
Descrizione:
Questa classe si occupa di mostrare sullo schermo

Funzioni:
1. Errori 
*/
#pragma once

#include <ncurses.h>

#include "level.hpp"
#include "size.hpp"
#include "changeable.hpp"


namespace manager {
    // Descrive la dimensione orizzontale della schermata di gioco
    const Size kGameWindowsSize  = {18,60};
    const int kSleepTime=50;
    class Display {
      private:
        Changeable<Size>* currentScreenSize_;
        // WINDOW di ncurses che contiene tutte le entità, muri
        // che sono mostrati al giocatore
        WINDOW *gameWin_ = nullptr;
        // crea la finestra di gioco
        void createGameWindow();
        bool handleSizeChange(Level* level);

        // distrugge la finestra di gioco
        void deleteGameWindow();

        Position getGameWindowPosition();


        Size updateScreenSize();

        Size getSizeWindow(WINDOW *win);

        void pauseLoop(Level* level);
        void runningLoop(Level* level);

      public:
        // TODO: Design-issue: 3 funzioni prendon il level manager come input
        // Dovrebbe essere un membro provato della classe?
        Display();

        ~Display();

        // crea la finestra e calcola il next frame
        void gameLoop(Level *levelManager);

        // fa il display degli oggetti
        void nextFrame(Level *levelManager,bool force);
    };
}