#include "collectables/power.hpp"

#include <mutex>
#include <stdlib.h>

#include "gamestruct/position.hpp"

namespace collectables {

    Power::Power(Position posObj)
        : Displayable(posObj, 'C') {}

    enums::CollisionType Power::getCollisionType() {
        return enums::CollisionType::POWER;
    }

}  // namespace collectables