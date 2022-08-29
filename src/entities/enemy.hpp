#pragma once

#include <mutex>

#include "collectables/artifact.hpp"
#include "collectables/power.hpp"
#include "entities/entity.hpp"
#include "enums/direction.hpp"
#include "gamestruct/displayable.hpp"
#include "gamestruct/logger.hpp"
#include "gamestruct/position.hpp"
#include "level/collidable.hpp"
#include "level/door-segment.hpp"
#include "level/wall-segment.hpp"

// Attualmente questa classe contiene un esempio di nemico
// che si muove e attacca il giocatore.
// Dovrebbe essere sostituito da un sistema per gestire ogni
// possibile nemico. (quindi un manager)
// oppure una factory per costruire il nemico specifico
namespace entities {
    class Enemy : public Entity {
      private:
        int coolDown_;
        int coolDownMax_;
        Logger logger_;
        virtual void _handleDoorCollision(manager::Level *levelManager, level::DoorSegment *door) override;
        virtual void _handleWallCollision(manager::Level *levelManager, level::WallSegment *wall) override;
        virtual void _handleEntityCollision(manager::Level *levelManager, Entity *entity) override;
        virtual void _handleArtifactCollision(manager::Level *levelManager, collectables::Artifact *artifact) override;
        virtual void _handlePowerCollision(manager::Level *levelManager, collectables::Power *power) override;
        virtual void _handleNoneCollision(manager::Level *levelManager) override;

      public:
        Enemy();
        Enemy(Position spawnPos);

        // int getDamage();

        void setPosition(Position pos);

        void wander();

        void resetCoolDown();

        void moveCoolDown();

        bool canMove();
    };
}  // namespace entities
