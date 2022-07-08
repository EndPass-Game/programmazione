#pragma once 
#include "enums/collision-type.hpp"
namespace level {
    // ogni classe che estenderà da questa sarà rappresentabile come 
    // un oggetto di collisione. È interfaccia per la collisione
    class Collidable {
    public:
        virtual enums::CollisionType getCollisionType() = 0; // pure virtual function
    };
}; // namespace level