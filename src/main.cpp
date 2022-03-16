#include <time.h>
#include <stdlib.h>

#include "game.hpp"


int main(){
    srand((unsigned int) time(NULL));

    manager::Game* gameInstance = manager::Game::GetInstance();
    gameInstance->run();
    delete gameInstance;
}
