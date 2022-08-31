#pragma once
#include "enums/collision-type.hpp"
namespace level {
    /**
     * @brief Classe astratta per rappresentare una collisione
     * ad ogni oggetto collidibile sarà associato un enum per identificarne
     * il tipo ed implementare un comportamento adeguato.
     */
    class Collidable {
      public:
        virtual enums::CollisionType getCollisionType() = 0;  // pure virtual function
    };
};  // namespace level
