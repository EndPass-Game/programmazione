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

    Display::Display():ResizableWindow() {
    }
    Display::Display(Level* level):ResizableWindow() {
        levelManager_=level;
    }

    Display::~Display()
    {
        deleteGameWindow();
    }

    void Display::createGameWindow()
    {
        // assert(win_==nullptr);
        Position pos=getGameWindowPosition();
        gameWin_ = newwin(
            kGameWindowsSize.x,
            kGameWindowsSize.y,
            /* Questi ultimi 2 valori descrivono l'offset della finestra */ pos.x, pos.y);

        // TODO: alcune funzioni di ncurses prendono parametri che non sono affatto ovvi
        // se si pensa che sia di difficile comprensione, potrebbe essere una buona
        // idea mettere un commento come newwin di sopra

    }

    void Display::deleteGameWindow()
    {
        // assert(win_!=nullptr);
        delwin(gameWin_);
        gameWin_ = nullptr;
    }

    Size Display::getSizeWindow(WINDOW *win)
    {
        return Size{getmaxx(win), getmaxy(win)};
    }

    Position Display::getGameWindowPosition(){
        Size screen=currentScreenSize_->getCurrent();
        int startY=(screen.y-kGameWindowsSize.y)/2;
        if(startY<0)startY=0;
        return {0,startY};
    }
    

    void Display::handleScreenSizeChange()
    {
        //when the screen size change
        deleteGameWindow();
        clear();
        createGameWindow();
        if (currentScreenSize_->getCurrent().x < kGameWindowsSize.x or currentScreenSize_->getCurrent().y < kGameWindowsSize.y)
        {
            levelManager_->gameState->setCurrent(enums::GameState::SCREEN_TO_SMALL);
        }
        else if (levelManager_->gameState->getCurrent() == enums::GameState::SCREEN_TO_SMALL)
        {
            levelManager_->gameState->setCurrent(enums::GameState::PAUSE);
        }
    }

    void Display::runningLoop()
    {
        clear();
        bool first = true;
        while (levelManager_->gameState->getCurrent() == enums::GameState::RUNNING)
        {
            // TODO: le variabili qui sopra non sono utilizzate, farle
            bool changed = updateScreenSize();
            changed |= first;
            nextFrame(changed);
            wrefresh(gameWin_);
            std::this_thread::sleep_for(std::chrono::milliseconds(kSleepTime));
        }
    }
    void Display::pauseLoop()
    {
        clear();
        while (levelManager_->gameState->getCurrent() == enums::GameState::PAUSE)
        {
            updateScreenSize();
            mvprintw(0, 0, "GameState Paused, click 'p' to resume");
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(kSleepTime));
        }
    }

    void Display::gameLoop()
    {

        createGameWindow();
        while (levelManager_->gameState->getCurrent() != enums::GameState::FINISH)
        {
            switch (levelManager_->gameState->getCurrent())
            {
            case enums::GameState::RUNNING:
                runningLoop();
                break;
            case enums::GameState::PAUSE:
                pauseLoop();
                break;
            case enums::GameState::SCREEN_TO_SMALL:
            {
                //TODO:va wrappato in una funzione es smallScreenLoop();
                while (levelManager_->gameState->getCurrent() == enums::GameState::SCREEN_TO_SMALL)
                {
                    updateScreenSize();
                    mvprintw(0, 0, "screen TO small");
                    refresh();
                    std::this_thread::sleep_for(std::chrono::milliseconds(kSleepTime));
                }
            }
            break;
            default:
                break;
            }
        }
        deleteGameWindow();
    }

    void Display::nextFrame(bool forceRebuild)
    {
        Player *player = levelManager_->player;

        // tutti gli oggetti devono essere cancellati se hanno cambiato la posizione
        player->move();
        player->clearLast(gameWin_);

        // tutti gli oggetti devono essere riprintati
        player->render(gameWin_, forceRebuild);
        //TODO:muri fatti male XD
        for (int i = 0; i < kGameWindowsSize.x; i++)
        {
            mvwprintw(gameWin_, i, 0, "#");
            mvwprintw(gameWin_, i, kGameWindowsSize.y - 1, "#");
        }
        for (int i = 0; i < kGameWindowsSize.y; i++)
        {
            mvwprintw(gameWin_, 0, i, "#");
            mvwprintw(gameWin_, kGameWindowsSize.x - 1, i, "#");
        }
    }
}