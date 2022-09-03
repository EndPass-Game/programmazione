#pragma once

#include "entities/entity.hpp"
#include "enums/direction.hpp"
#include "gamestruct/movable.hpp"
#include "gamestruct/position.hpp"
#include "manager/level.fwd.h"
// ha bisogno di fare danno
// di muoversi
// di essere distrutto quanto colpisce qualcosa (anche una entità)

namespace weapon {
    class Bullet : public Movable {
      private:
        int damage_;
        bool isDestroyed_;

      public:
        Bullet(Position position, enums::Direction direction, int damage = 1);

        bool hasHit();

        bool handleEntityHit(Entity *entity);

        void move();

        bool checkCollision(manager::Level *levelManager);

        void render(WINDOW *win, bool force) override;

        virtual void act(manager::Level *levelManager) override;

        bool isDestroyed() const;
    };
}  // namespace weapon