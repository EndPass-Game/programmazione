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
        //mantiene una struttura che ricorda lo stato vecchio della size
        Changeable<Size>* currentScreenSize_;
        // WINDOW di ncurses che contiene tutte le entità, muri
        // che sono mostrati al giocatore
        WINDOW *gameWin_ = nullptr;
        // crea la finestra di gioco
        void createGameWindow();
        //esegue delle operazioni in base a come si è modificata la dimensione
        // setta lo stato Game to small e le varie schermate
        bool  handleScreenSizeChange(Level* level);

        // distrugge la finestra di gioco
        void deleteGameWindow();

        //funzione che calcola la posizione della finestra di gioco per centrarla
        Position getGameWindowPosition();

        //ricalcola la screen size guardando anche se cambia
        void updateScreenSize();

        //TODO:funzione non utilizzata, ma potrebbe servire in un futuro
        Size getSizeWindow(WINDOW *win);

        //funzione che viene eseguita quando il programma entra nello stato di pausa
        //e finisce di eseguire quando cambia stato
        void pauseLoop(Level* level);

        //funzione che viene eseguita quando il programma entra nello stato di running
        //e finisce di eseguire quando cambia stato
        void runningLoop(Level* level);

      public:
        // TODO: Design-issue: 3 funzioni prendon il level manager come input
        // Dovrebbe essere un membro provato della classe?
        Display();

        ~Display();

        // crea la finestra e calcola il next frame
        void gameLoop(Level *levelManager);

        //mostra gli oggetti a video, e li muove, se force è true foza gli oggetti ad essere riprintati
        void nextFrame(Level *levelManager,bool force);
    };
}