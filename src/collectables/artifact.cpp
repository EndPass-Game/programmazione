#include "collectables/artifact.hpp"

#include <mutex>
#include <stdlib.h>

#include "gamestruct/position.hpp"

namespace collectables {

    Artifact::Artifact(int life, Position posObj)
        : Displayable(posObj, 'A') {
        lifeUpgrade_ = life;
    }

    int Artifact::getLifeUpgrade() {
        return this->lifeUpgrade_;
    }

    enums::CollisionType Artifact::getCollisionType() {
        return enums::CollisionType::ARTIFACT;
    }

}  // namespace collectables