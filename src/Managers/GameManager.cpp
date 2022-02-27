#include "GameManager.hpp"
#include <thread>

GameManager* GameManager::instance=nullptr;

GameManager::GameManager(){
    //istanza di Input Manager
    //istanza level Manager
    inputManager.levelManager=(&levelManager);
    displayManager.levelManager=(&levelManager);
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
    std::thread inputThread(&InputManager::runInputManager,inputManager);
    inputThread.detach();
    std::thread displayThread(&DisplayManager::gameLoop,displayManager);
    inputThread.join();
    //fine gioco
}




