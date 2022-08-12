#include "manager/game.hpp"

#include <thread>

#include "manager/display.hpp"
#include "manager/input.hpp"
#include "manager/level.hpp"
#include "views/menu-view.hpp"

namespace manager {

    Game::Game()
        : logger_("GAME") {
        logger_.info("Initializing main objects of the game");
        viewManager_ = new ViewManager();
        inputManager_ = new Input(viewManager_);
        displayManager_ = new Display(viewManager_);

        initscr();             // inizializza lo schermo di ncurses
        noecho();              // impedisce la stampa a schermo del carattere di getch()
        keypad(stdscr, TRUE);  // permette a wgetch() di prendere in input caratteri funzione
        logger_.info("object initialized");
    }

    Game::~Game() {
        delete viewManager_;
        delete inputManager_;
        delete displayManager_;
        endwin();
    }

    void Game::run() {
        logger_.info("Game created, starting game...");

        views::MenuView *menu = new views::MenuView();
        viewManager_->pushView(menu);

        logger_.info("starting input thread");
        std::thread inputThread(&Input::run, inputManager_);
        inputThread.detach();

        logger_.info("starting main gameLoop");
        std::thread displayThread(&Display::gameLoop, displayManager_);
        displayThread.join();
    }
}  // namespace manager