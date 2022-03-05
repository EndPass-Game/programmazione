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


namespace manager {
    // Descrive la dimensione orizzontale della schermata di gioco
    const int kWindowSizeX = 15;

    // Descrive la dimensione verticale della schermata di gioco
    const int kWindowSizeY = 25;

    class Display {
      private:
        // WINDOW di ncurses che contiene tutte le entità, muri
        // che sono mostrati al giocatore
        WINDOW *gameWin_ = nullptr;
        // crea la finestra di gioco
        void createGameWindow();

        // distrugge la finestra di gioco
        void deleteGameWindow();

        Size getSizeScreen();

        Size getSizeWindow(WINDOW* win);

        

      public:

        // TODO: Design-issue: 3 funzioni prendon il level manager come input
        // Dovrebbe essere un membro provato della classe?
        Display();

        // ~DisplayManager();

        // crea la finestra e calcola il next frame
        void gameLoop(Level* levelManager);

        // fa il display degli oggetti
        void nextFrame(Level* levelManager);

    };
}