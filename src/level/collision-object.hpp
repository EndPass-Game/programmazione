#pragma once 

#include "enums/collision-type.hpp"
#include "level/collidable.hpp"

namespace level {
    struct CollisionObject {
        enums::CollisionType type; 
        Collidable *collidable;

        CollisionObject(enums::CollisionType type, Collidable *collidable) :
            type(type), collidable(collidable) {};
    };
};