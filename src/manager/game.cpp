#include "manager/game.hpp"

#include <thread>

#include "manager/level.hpp"
#include "manager/display.hpp"
#include "manager/input.hpp"
#include "views/menuView.hpp"

namespace manager
{
    Game::Game()
    {
        // inizializza i managers
        viewManager_ = new ViewManager();
        inputManager_ = new Input(viewManager_);
        displayManager_ = new Display(viewManager_);

        initscr();            // inizializza lo schermo di ncurses
        noecho();             // impedisce la stampa a schermo del carattere di getch()
        keypad(stdscr, TRUE); // permette a wgetch() di prendere in input caratteri funzione
    }

    Game::~Game()
    {
        delete inputManager_;
        delete displayManager_;
        endwin();
    }
    void Game::run()
    {
        views::MenuView* menu=new views::MenuView();
        viewManager_->pushView(menu);
        std::thread inputThread(&Input::run, inputManager_);
        inputThread.detach();
        std::thread displayThread(&Display::gameLoop, displayManager_);
        displayThread.join();
    }
}