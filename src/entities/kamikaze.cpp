#include "entities/kamikaze.hpp"

#include <mutex>
#include <stdlib.h>

namespace entities{
    Kamikaze::Kamikaze()
        : Enemy(){}
    
    Kamikaze::Kamikaze(Position pos)
        :Enemy(pos){}
    
    enums::EnemyType Kamikaze::getEnemyType(){
        return enums::EnemyType::KAMIKAZE;
    }
}