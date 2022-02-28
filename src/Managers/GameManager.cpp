#include "GameManager.hpp"
#include <thread>

GameManager* GameManager::instance=nullptr;

GameManager::GameManager(){
    //istanza di Input Manager
    //istanza level Manager
}
//crea il singleton o restituisce l'oggetto statico
GameManager* GameManager::GetInstance(){
    
    if(GameManager::instance==nullptr){
        GameManager::instance=new GameManager();
    }
    return GameManager::instance;
}
void GameManager::run(){
    //inizio gioco
    std::thread inputThread(&InputManager::runInputManager,inputManager,&levelManager);
    inputThread.detach();
    std::thread displayThread(&DisplayManager::gameLoop,displayManager,&levelManager);
    inputThread.join();
    //fine gioco
}




