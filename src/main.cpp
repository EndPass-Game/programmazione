#include <stdlib.h>
#include <time.h>

#include "gamestruct/logger.hpp"
#include "loader/level-provider.hpp"
#include "manager/game.hpp"

int main() {
    Logger logger("START", "game.log", "w");
    srand((unsigned int) time(NULL));

    loader::LevelProvider::getInstance().loadLevels();

    manager::Game gameInstance;
    gameInstance.run();
}
