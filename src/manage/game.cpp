#include <thread>

#include "game.hpp"

#include "display.hpp"
#include "input.hpp"

namespace manager {
    Game* Game::instance_ = nullptr;

    Game::Game() {
        // istanza di Input Manager
        // istanza level Manager
        initscr();
        noecho();
        keypad(stdscr, TRUE); // TODO: commentino o creazione di variabile con nome per spiegare questa?
    }

    // crea il singleton o restituisce l'oggetto statico
    Game* Game::GetInstance() {
        if(Game::instance_ == nullptr) {
            Game::instance_ = new Game();
        }
        return Game::instance_;
    }

    void Game::run() {
        // fai vedere il menu
        // crea il livello in base al menu    
        std::thread inputThread(&Input::run, inputManager_, &levelManager_);
        inputThread.detach();
        std::thread displayThread(&Display::gameLoop, displayManager_, &levelManager_);
        displayThread.join();

        // TODO: da mettere nel decostruttore
        endwin();
    }
}