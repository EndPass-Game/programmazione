#pragma once
/*
deve tenere le vite, artefatti, posizione, e items
*/
#include "manager/level.fwd.h" // circlular import

#include "enums/direction.hpp"
#include "enums/direction.hpp"
#include "gamestruct/displayable.hpp"
#include "gamestruct/position.hpp"
// TODO: invece che ogni classe figlia erediti da questa
// sarebbe buona cosa rendere questa classe una factory
// che sforni entità, ognuna settata con certe specifiche
class Entity: public Displayable {
  protected:
    int life_;      // quantità di vita
    int attack_;    // danno fatto alle altre entità

    // Contiene la direzione che dovrà essere intrapresa nel prossimo frame
    enums::Direction direction_;
  public:
    Entity();
    Entity(int life, int attack);
    Entity(int life, int attack, Position current, char displayChar);
    virtual ~Entity() = default;
    bool isDead() const;

    // sarà definita a seconda del metodo d'attacco dell'entità
    virtual void attack(Entity *target);

    // muove l'entità secondo la direzione impostata
    void move(manager::Level *levelManager);

    void applyDamage(int damage);

    void setDirection(enums::Direction direction);
};