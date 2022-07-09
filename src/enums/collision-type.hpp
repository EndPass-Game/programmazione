#pragma once 

namespace enums {
    // descrive l'oggetto con cui si è colliso 
    enum class CollisionType {
        NONE = 0,
        WALLSEGMENT = 1,
        ENTITY = 2,
        ARTIFACT = 3,
        POWER = 4,
        DOOR = 5,
        DOORCLOSED = 6,
    };
}; // namespace enums 
