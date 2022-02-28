/*
Descrizione:
Questa classe si occupa di mostrare sullo schermo

Funzioni:
1. Errori 
*/
#include "DisplayManager.hpp"

DisplayManager::DisplayManager(){}

void DisplayManager::gameLoop(LevelManager* levelManager){
	//create windows
    win = newwin(levelManager->WINDOWS_SIZE_X,levelManager->WINDOWS_SIZE_Y, 0, 0);
    box(win, 1 , 1);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    refresh();
	int max_x=getmaxx(stdscr);
	int max_y=getmaxy(stdscr);
	while(levelManager->isRunning){
        nextFrame();
    	std::this_thread::sleep_for (std::chrono::milliseconds(300));
	}
	//clean up
    wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(win);
    delwin(win);
}


void DisplayManager::nextFrame(){
}
