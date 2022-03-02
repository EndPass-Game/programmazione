#include "GameManager.hpp"

GameManager* GameManager::instance=nullptr;

GameManager::GameManager(){
    //istanza di Input Manager
    //istanza level Manager
    initscr();
    noecho();
    keypad(stdscr, TRUE);
}
//crea il singleton o restituisce l'oggetto statico
GameManager* GameManager::GetInstance(){
    
    if(GameManager::instance==nullptr){
        GameManager::instance = new GameManager();
    }
    return GameManager::instance;
}
void GameManager::run()
{
    //inizio gioco
    // while(){
        //fai vedere il menu
        //crea il livello in base al menu    
        std::thread inputThread(&InputManager::runInputManager, inputManager, &levelManager);
        inputThread.detach();
        std::thread displayThread(&DisplayManager::gameLoop, displayManager, &levelManager);
        displayThread.join();
    //}
    //fine gioco
    //TODO: da mettere nel decostruttore
    endwin();
}
