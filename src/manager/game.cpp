#include "manager/game.hpp"

#include <thread>

#include "manager/level.hpp"
#include "manager/display.hpp"
#include "manager/input.hpp"

namespace manager {
    Game *Game::instance_ = nullptr;

    Game::Game() {
        // inizializza i managers 
        levelInstance_ = new Level();
        inputManager_ = new Input();
        displayManager_ = new Display();

        initscr(); // inizializza lo schermo di ncurses
        noecho(); // impedisce la stampa a schermo del carattere di getch()
        keypad(stdscr, TRUE); // permette a wgetch() di prendere in input caratteri funzione
    }

    Game::~Game() {
        delete levelInstance_;
        delete inputManager_;
        delete displayManager_;
        endwin();
    }

    // crea il singleton o restituisce l'oggetto statico
    Game* Game::GetInstance() {
        if(Game::instance_ == nullptr) {
            Game::instance_ = new Game();
        }
        return Game::instance_;
    }

    Level *Game::getLevelManager() const {
        return levelInstance_;
    }

    void Game::run() {
        std::thread inputThread(&Input::run, inputManager_);
        inputThread.detach();
        std::thread displayThread(&Display::gameLoop, displayManager_);
        displayThread.join();
    }
}