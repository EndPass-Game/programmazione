#include <stdlib.h>
#include <time.h>

#include "gamestruct/logger.hpp"
#include "manager/game.hpp"
int main() {
    srand((unsigned int) time(NULL));

    manager::Game gameInstance;

    Logger logger("START", "game.log", "w");
    logger.info("Game created, starting game...");

    gameInstance.run();
}
