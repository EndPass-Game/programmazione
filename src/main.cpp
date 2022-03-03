
#include "game.hpp"


int main(){
    
    manager::Game* gameInstance = manager::Game::GetInstance();
    gameInstance->run();
    delete gameInstance;
}
