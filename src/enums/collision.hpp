#pragma once 

namespace enums {
    // descrive l'oggetto con cui si è colliso 
    enum class CollisionObject {
        NONE = 0,
        WALL = 1,
        ENTITY = 2,
        ARTIFACT = 3,
        POWER = 4,
        PLAYER = 5,
    };
}; // namespace enums 
