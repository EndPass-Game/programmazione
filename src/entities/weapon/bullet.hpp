#pragma once

#include "entities/entity.hpp"
#include "enums/direction.hpp"
#include "gamestruct/movable.hpp"
#include "gamestruct/position.hpp"

// ha bisogno di fare danno
// di muoversi
// di essere distrutto quanto colpisce qualcosa (anche una entità)

namespace weapon {
    class Bullet : public Movable {
      private:
        int damage_;

      public:
        Bullet(Position position, enums::Direction direction, int damage = 1);

        bool hasHit();

        // TODO(SIMO):
        void handleEntityHit(Entity *entity);

        void move();
    };
}  // namespace weapon