/*
Descrizione:
Questa classe si occupa di mostrare sullo schermo

Funzioni:
1. Errori 
*/
#include "DisplayManager.hpp"

DisplayManager::DisplayManager(){

}

void DisplayManager::createWindow(LevelManager* levelManager){
    //assert(win==nullptr);
    win = newwin(levelManager->WINDOWS_SIZE_X,levelManager->WINDOWS_SIZE_Y, 0, 0);
    box(win, 1 , 1);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(win);
}
void DisplayManager::deleteWindow()
{
    //assert(win!=nullptr);
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);
    delwin(win);
    win = nullptr;
}


void DisplayManager::gameLoop(LevelManager *levelManager)
{
    //create windows
    createWindow(levelManager);
    while (levelManager->gameState != GameState::FINISH)
    {
        while (levelManager->gameState == GameState::RUNNING)
        {
            int current_x = getmaxx(stdscr);
            int current_y = getmaxy(stdscr);

            nextFrame(levelManager);

            wrefresh(win);
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
    }
    //clean up
    deleteWindow();
}

void DisplayManager::nextFrame(LevelManager *levelManager)
{
    Player *player = levelManager->player;
    //tutti gli oggetti devono essere cancellati se hanno cambiato la posizione
    player->move(levelManager);

    player->clearLast(win);
    //tutti gli oggetti devono essere riprintati
    player->render(win);
}
