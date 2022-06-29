/*
deve tenere le vite, artefatti, posizione, e items
*/

#pragma once

#include "enums/direction.hpp"
#include "gamestruct/displayable.hpp"
#include "gamestruct/position.hpp"
#include "enums/direction.hpp"
#include "manager/display.hpp" // TODO: rimuovere questo import per le costanti di win quando si avrà il sistema per detection collisioni

// TODO: invece che ogni classe figlia erediti da questa
// sarebbe buona cosa rendere questa classe una factory
// che sforni entità, ognuna settata con certe specifiche
class Entity: public Displayable {
  protected:
    int life_;      // quantità di vita
    int attack_;    // danno fatto alle altre entità

    // Contiene la direzione che dovrà essere intrapresa nel prossimo frame
    enums::Direction direction_;
    
    // Permette un update thread safe 
  public:
    Entity(int life, int attack);
    Entity(int life, int attack, Position current, char displayChar);

    // sarà definita a seconda del metodo d'attacco dell'entità
    virtual void attack(Entity *target);

    // muove l'entità secondo la direzione impostata
    void move();

    // funzione che fa il check se è possibile andare in una certa posizione
    bool canMove(int x, int y) const;

    bool isDead() const;

    void applyDamage(int damage);

    void setDirection(enums::Direction direction);
};