#pragma once

#include "collectables/artifact.hpp"
#include "collectables/power.hpp"
#include "entities/entity.hpp"
#include "enums/direction.hpp"
#include "gamestruct/displayable.hpp"
#include "gamestruct/logger.hpp"
#include "gamestruct/position.hpp"
#include "gamestruct/string-utility.hpp"
#include "level/collidable.hpp"
#include "level/door-segment.hpp"
#include "level/wall-segment.hpp"

// Player: classe che contiene il personaggio
class Player : public Entity {
  private:
    int powers_;
    int score_;
    int coolDown_;
    int coolDownMax_;
    int maxLife_;

    Logger logger_;

    virtual void _handleDoorCollision(manager::Level *levelManager, level::DoorSegment *door) override;
    virtual void _handleArtifactCollision(manager::Level *levelManager, collectables::Artifact *artifact) override;
    virtual void _handlePowerCollision(manager::Level *levelManager, collectables::Power *power) override;

  public:
    Player();

    void addPower();

    void removePower();

    int getPowers();

    int getScore();

    void setPosition(Position pos);

    void incrementScore(int increment);

    void resetCoolDown();

    void coolDown();

    bool canFire();

    void attack(manager::Level *levelManager) override;

    void act(manager::Level *levelManager) override;
};