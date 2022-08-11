#include "collectables/power.hpp"

#include <mutex>
#include <stdlib.h>

#include "entities/entity.hpp"
#include "enums/direction.hpp"
#include "gamestruct/position.hpp"

namespace collectables {

    Power::Power(Position posObj)
        : Displayable(posObj, 'C') {}

    enums::CollisionType Power::getCollisionType() {
        return enums::CollisionType::POWER;
    }

}  // namespace collectables