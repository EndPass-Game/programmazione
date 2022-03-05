/*
Descrizione:
Questa classe si occupa di mostrare sullo schermo

Funzioni:
1. Errori 
*/
#include <chrono>
#include <thread>

#include "display.hpp"
#include "level.hpp"


namespace manager {

    Display::Display() {

    }

    void Display::createGameWindow() {
        // assert(win_==nullptr);
        gameWin_ = newwin(
            kWindowSizeX, 
            kWindowSizeY,
            /* Questi ultimi 2 valori descrivono l'offset della finestra */ 0, 0);
        
        // TODO: alcune funzioni di ncurses prendono parametri che non sono affatto ovvi
        // se si pensa che sia di difficile comprensione, potrebbe essere una buona
        // idea mettere un commento come newwin di sopra
        
        box(gameWin_, 1, 1);
        wborder(gameWin_, '#', '#', '#', '#', '#', '#', '#', '#');
        wrefresh(gameWin_);
    }

    void Display::deleteGameWindow() {
        // assert(win_!=nullptr);
        wborder(gameWin_, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        wrefresh(gameWin_);
        gameWin_ = nullptr;
    } 

    Size Display::getSizeWindow(WINDOW* win){
        return Size{getmaxx(win),getmaxy(win)};
    }
    Size Display::getSizeScreen(){
        return Size{COLS,LINES};
    }

    void Display::gameLoop(Level *levelManager) {
        
        createGameWindow();
        while (levelManager->gameState != enums::GameState::FINISH) {
            while (levelManager->gameState == enums::GameState::RUNNING) {
                int current_x = getmaxx(stdscr);
                int current_y = getmaxy(stdscr);
                // TODO: le variabili qui sopra non sono utilizzate, farle

                nextFrame(levelManager);

                wrefresh(gameWin_);
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
            }
        }
        deleteGameWindow();
    }

    void Display::nextFrame(Level *levelManager) {
        Player *player = levelManager->player;

        // tutti gli oggetti devono essere cancellati se hanno cambiato la posizione
        player->move();
        player->clearLast(gameWin_);

        // tutti gli oggetti devono essere riprintati
        player->render(gameWin_);
    }
}