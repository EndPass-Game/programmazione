#include <time.h>
#include <stdlib.h>

#include "manager/game.hpp"

int main()
{
    srand((unsigned int)time(NULL));
    manager::Game gameInstance;
    gameInstance.run();
}
