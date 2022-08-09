#include "collectables/power.hpp"

#include <stdlib.h>
#include <mutex>

#include "gamestruct/position.hpp"
#include "enums/direction.hpp"
#include "entities/entity.hpp"

namespace collectables {

Power::Power(Position posObj):
    Displayable(posObj, 'C') {}



enums::CollisionType Power::getCollisionType() {
    return enums::CollisionType::POWER;
}
        
} // namespace collectables