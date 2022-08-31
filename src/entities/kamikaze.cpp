#include "entities/kamikaze.hpp"

#include <mutex>
#include <stdlib.h>

namespace entities{
    Kamikaze::Kamikaze()
        : Enemy('K'){}
    
    Kamikaze::Kamikaze(Position pos)
        :Enemy(pos, 7, 'K'){}
    
    enums::EnemyType Kamikaze::getEnemyType(){
        return enums::EnemyType::KAMIKAZE;
    }
}