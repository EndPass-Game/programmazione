#include "GameManager.hpp"

GameManager::GameManager(){
    //istanza di Input Manager
    //istanza level Manager
}
GameManager* GameManager::GetInstance(){
    if(GameManager::instance==nullptr){
        GameManager::instance=new GameManager();
    }
    return GameManager::instance;
}
void GameManager::run(){
    //istanza di Input Manager
    //istanza level Manager
    

}




