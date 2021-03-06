#include "collectables/artifact.hpp"

#include <stdlib.h>
#include <mutex>

#include "gamestruct/position.hpp"
#include "enums/direction.hpp"
#include "entities/entity.hpp"


Artifact::Artifact(int life, Position posObj):
    Displayable(posObj, 'A'){
        lifeUpgrade_ = life;
}

int Artifact::getLifeUpgrade(){
    return this->lifeUpgrade_;
}

enums::CollisionType Artifact::getCollisionType() {
    return enums::CollisionType::ARTIFACT;
}
    
    