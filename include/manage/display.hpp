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
#include "resizableWindow.hpp"


namespace manager {
    // Descrive la dimensione orizzontale della schermata di gioco
    const Size kGameWindowsSize  = {18,60};
    const int kSleepTime=50;
    class Display: public ResizableWindow{
      private:
        // WINDOW di ncurses che contiene tutte le entità, muri
        // che sono mostrati al giocatore
        WINDOW *gameWin_ = nullptr;
        Level *levelManager_;
        // crea la finestra di gioco
        void createGameWindow();

        // distrugge la finestra di gioco
        void deleteGameWindow();


        void handleScreenSizeChange();

        //funzione che calcola la posizione della finestra di gioco per centrarla
        Position getGameWindowPosition();

        //TODO:funzione non utilizzata, ma potrebbe servire in un futuro
        Size getSizeWindow(WINDOW *win);

        //funzione che viene eseguita quando il programma entra nello stato di pausa
        //e finisce di eseguire quando cambia stato
        void pauseLoop();

        //funzione che viene eseguita quando il programma entra nello stato di running
        //e finisce di eseguire quando cambia stato
        void runningLoop();

      public:
        // TODO: Design-issue: 3 funzioni prendon il level manager come input
        // Dovrebbe essere un membro provato della classe?
        Display();
        Display(Level* level);

        ~Display();

        // crea la finestra e calcola il next frame
        void gameLoop();

        //mostra gli oggetti a video, e li muove, se force è true foza gli oggetti ad essere riprintati
        void nextFrame(bool force);
    };
}