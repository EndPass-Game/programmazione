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

        /**
         * @brief applica il danno alla collisione, se possibile (solo entity).
         * @returns se ha colliso o meno.
         */
        bool _handleCollision(manager::Level *levelManager, level::Collidable *collision);

      public:
        Bullet(Position position, enums::Direction direction, int damage = 1);

        bool hasHit();

        bool handleEntityHit(Entity *entity);

        void move();

        /**
         * @brief gestisce il danno all'entità alla prossima collisione
         * @returns true se il proiettile ha avuto una collisione
         */
        bool checkCollision(manager::Level *levelManager);

        void render(WINDOW *win, bool force) override;

        virtual void act(manager::Level *levelManager) override;

        bool isDestroyed() const;
    };
}  // namespace weapon