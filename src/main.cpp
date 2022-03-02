
#include "GameManager.hpp"


int main(){
    
    GameManager* gameInstance=GameManager::GetInstance();
    gameInstance->run();
    delete gameInstance;
}
