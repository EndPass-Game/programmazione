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
        currentScreenSize_=new Changeable<Size>({LINES,COLS});
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

    Size Display::updateScreenSize()
    {
        Size newSize={LINES,COLS};
        currentScreenSize_->setCurrent(newSize);
        return newSize;
    }


    Position Display::getGameWindowPosition(){
        Size screen=currentScreenSize_->getCurrent();
        int startY=(screen.y-kGameWindowsSize.y)/2;
        if(startY<0)startY=0;
        return {0,startY};
    }
    

    bool Display::handleSizeChange(Level* levelManager)
    {
        updateScreenSize();
        bool isChanged=currentScreenSize_->isChanged();
        if (isChanged)
        {
            //when the screen size change
            deleteGameWindow();
            clear();
            createGameWindow();
        }
        if (currentScreenSize_->getCurrent().x < kGameWindowsSize.x 
            and currentScreenSize_->getCurrent().y < kGameWindowsSize.y)
        {
            levelManager->gameState=enums::GameState::SCREEN_TO_SMALL;
        }

        return isChanged;
    }

    void Display::runningLoop(Level *levelManager)
    {
        while (levelManager->gameState == enums::GameState::RUNNING)
        {
            // TODO: le variabili qui sopra non sono utilizzate, farle
            bool changed = handleSizeChange(levelManager);
            nextFrame(levelManager, changed);
            wrefresh(gameWin_);
            std::this_thread::sleep_for(std::chrono::milliseconds(kSleepTime));
        }
    }
    void Display::pauseLoop(Level *levelManager)
    {
        while (levelManager->gameState == enums::GameState::PAUSE)
        {
            handleSizeChange(levelManager);
            mvprintw(0, 0, "GameState Paused");
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(kSleepTime));
        }
    }

    void Display::gameLoop(Level *levelManager)
    {

        createGameWindow();
        while (levelManager->gameState != enums::GameState::FINISH)
        {
            switch (levelManager->gameState)
            {
            case enums::GameState::RUNNING:
                runningLoop(levelManager);
                break;
            case enums::GameState::PAUSE:
                pauseLoop(levelManager);
                break;
            case enums::GameState::SCREEN_TO_SMALL:
            {
                //TODO:va wrappato in una funzione es smallScreenLoop();
                while (levelManager->gameState == enums::GameState::SCREEN_TO_SMALL)
                {
                    handleSizeChange(levelManager);
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

    void Display::nextFrame(Level *levelManager, bool forceRebuild)
    {
        Player *player = levelManager->player;

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