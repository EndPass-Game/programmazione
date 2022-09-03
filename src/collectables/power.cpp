#include "collectables/power.hpp"

#include <mutex>
#include <stdlib.h>

#include "gamestruct/position.hpp"

namespace collectables {

    Power::Power(Position posObj, int id)
        : Displayable(posObj, 'C'), id_(id) {}

    int Power::getId() {
        return id_;
    }

    enums::CollisionType Power::getCollisionType() {
        return enums::CollisionType::POWER;
    }
}  // namespace collectables