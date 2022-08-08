#include <time.h>
#include <stdlib.h>

#include "manager/game.hpp"
#include "gamestruct/logger.hpp"
int main()
{
    srand((unsigned int)time(NULL));


    manager::Game gameInstance;

    Logger logger("START", "game.log", "w");
    logger.debug("Game created, starting game...");

    gameInstance.run();
}
