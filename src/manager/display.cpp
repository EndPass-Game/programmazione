/*
Descrizione:
Questa classe si occupa di mostrare sullo schermo

Funzioni:
1. Errori 
*/
#include "manager/display.hpp"

#include <chrono>
#include <thread>

#include "manager/game.hpp" // level manager
#include "manager/level.hpp"


namespace manager {

    Display::Display() {
        currentScreenSize_ = new Changeable<Size>({LINES,COLS});
        currFrameTime_ = 0;
    }

    Display::~Display()
    {
        delete currentScreenSize_;
        deleteGameWindow();
    }

    void Display::createGameWindow()
    {
        // assert(win_==nullptr);
        Position pos=getGameWindowPosition();
        gameWin_ = newwin(
            kGameWindowsSize.riga,
            kGameWindowsSize.colonna,
            /* Questi ultimi 2 valori descrivono l'offset della finestra */ pos.riga, pos.colonna);

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

    Size Display::getSizeWindow(WINDOW *win) const
    {
        return Size{getmaxx(win), getmaxy(win)};
    }

    void Display::updateScreenSize()
    {
        Size newSize={LINES,COLS};
        currentScreenSize_->setCurrent(newSize);
    }


    Position Display::getGameWindowPosition(){
        Size screen=currentScreenSize_->getCurrent();
        int startY=(screen.colonna-kGameWindowsSize.colonna)/2;
        if(startY<0)startY=0;
        return {0,startY};
    }
    

    bool Display:: handleScreenSizeChange()
    {
        Level *levelManager = Game::GetInstance()->getLevelManager();
        updateScreenSize();
        bool isChanged=currentScreenSize_->isChanged();
        if (isChanged)
        {
            //when the screen size change
            deleteGameWindow();
            clear();
            createGameWindow();
            if (currentScreenSize_->getCurrent().riga < kGameWindowsSize.riga or currentScreenSize_->getCurrent().colonna < kGameWindowsSize.colonna)
            {
                levelManager->gameState->setCurrent(enums::GameState::SCREEN_TO_SMALL);
            }
            else if (levelManager->gameState->getCurrent() == enums::GameState::SCREEN_TO_SMALL)
            {
                levelManager->gameState->setCurrent(enums::GameState::PAUSE);
            }
        }

        return isChanged;
    }

    void Display::runningLoop()
    {
        Level *levelManager = Game::GetInstance()->getLevelManager();
        clear();
        bool first = true;
        while (levelManager->gameState->getCurrent() == enums::GameState::RUNNING)
        {
            // TODO: le variabili qui sopra non sono utilizzate, farle
            bool changed =  handleScreenSizeChange();
            changed |= first;
            nextFrame(changed);
            wrefresh(gameWin_);
            std::this_thread::sleep_for(std::chrono::milliseconds(kSleepTime));
        }
    }

    void Display::pauseLoop()
    {
        Level *levelManager = Game::GetInstance()->getLevelManager();
        clear();
        while (levelManager->gameState->getCurrent() == enums::GameState::PAUSE)
        {
            handleScreenSizeChange();
            mvprintw(0, 0, "GameState Paused, click 'p' to resume");
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(kSleepTime));
        }
    }

    void Display::gameLoop()
    {
        Level *levelManager = Game::GetInstance()->getLevelManager();
        createGameWindow();
        while (levelManager->gameState->getCurrent() != enums::GameState::FINISH)
        {
            switch (levelManager->gameState->getCurrent())
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
                while (levelManager->gameState->getCurrent() == enums::GameState::SCREEN_TO_SMALL)
                {
                    handleScreenSizeChange();
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

    void Display::updateObjects(bool forceRebuild) {   
        Level *levelManager = Game::GetInstance()->getLevelManager();
        Player *player = levelManager->player;
        // TODO: gestire in seguito quando enemy diventa una lista, o collezione
        // di nemici
        Enemy *enemy = levelManager->enemy;

        player->move();
        player->clearLast(gameWin_);
        player->render(gameWin_, forceRebuild);

        // TODO: in questa parte si dovrebbero updatare tutte le entità
        // o qualunque cosa si deve muovere o fare
        currFrameTime_ += 1;
        if (currFrameTime_ >= kObjectTimer) {
            enemy->wander();
            enemy->move();
            enemy->clearLast(gameWin_);
            enemy->render(gameWin_, forceRebuild);
            currFrameTime_ = 0;
        }
    }

    void Display::nextFrame(bool forceRebuild)
    {
        updateObjects(forceRebuild);
        //TODO:muri fatti male XD
        for (int i = 0; i < kGameWindowsSize.riga; i++)
        {
            mvwprintw(gameWin_, i, 0, "#");
            mvwprintw(gameWin_, i, kGameWindowsSize.colonna - 1, "#");
        }
        for (int i = 0; i < kGameWindowsSize.colonna; i++)
        {
            mvwprintw(gameWin_, 0, i, "#");
            mvwprintw(gameWin_, kGameWindowsSize.riga - 1, i, "#");
        }
    }
} // namespace manager