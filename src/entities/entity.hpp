#pragma once

#include "collectables/artifact.hpp"
#include "collectables/power.hpp"
#include "enums/direction.hpp"
#include "gamestruct/movable.hpp"
#include "gamestruct/position.hpp"
#include "level/collidable.hpp"
#include "level/door-segment.hpp"
#include "level/wall-segment.hpp"
#include "manager/level.fwd.h"  // circlular import

// TODO: invece che ogni classe figlia erediti da questa
// sarebbe buona cosa rendere questa classe una factory
// che sforni entità, ognuna settata con certe specifiche
class Entity : public Movable, public level::Collidable {
  protected:
    int life_;    // quantità di vita
    int attack_;  // danno fatto alle altre entità

    virtual void _handleDoorCollision(manager::Level *levelManager, level::DoorSegment *door);
    virtual void _handleWallCollision(manager::Level *levelManager, level::WallSegment *wall);
    virtual void _handleEntityCollision(manager::Level *levelManager, Entity *entity);
    virtual void _handleArtifactCollision(manager::Level *levelManager, collectables::Artifact *artifact);
    virtual void _handlePowerCollision(manager::Level *levelManager, collectables::Power *power);
    virtual void _handleNoneCollision(manager::Level *levelManager);

  public:
    Entity();
    Entity(int life, int attack);
    Entity(int life, int attack, Position current, char displayChar);
    virtual ~Entity() = default;
    bool isDead() const;

    // metodo virtuale che sarà definita a
    // seconda del metodo d'attacco dell'entità
    virtual void attack(Entity *target);

    // muove l'entità secondo la direzione impostata
    void move(manager::Level *levelManager);

    void applyDamage(int damage);

    int getLife();

    void setLife(int life);

    virtual enums::CollisionType getCollisionType() override;
};