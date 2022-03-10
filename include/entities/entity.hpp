/*
deve tenere le vite, artefatti, posizione, e items
*/

#pragma once

#include "displayable.hpp"
#include "direction.hpp"
#include "position.hpp"

// TODO: invece che ogni classe figlia erediti da questa
// sarebbe buona cosa rendere questa classe una factory
// che sforni entità, ognuna settata con certe specifiche
class Entity: public Displayable {
  protected:
    int life_;      // quantità di vita
    int attack_;    // danno fatto alle altre entità
    int defense_;   // difesa costante dell'entità
    int shield_;    // difesa temporanea che si può rompere

    // Contiene la direzione che dovrà essere intrapresa nel prossimo frame
    enums::Direction direction_;
    // Permette un update thread safe 
    std::mutex mutex_;

  public:
    Entity(int life, int attack, int defense = 0, int shield = 0);
    Entity(int life, int attack, int defense, int shield, 
        Position current,
        char displayChar);

    // muove l'entità secondo la direzione impostata
    void move();

    // funzione che fa il check se è possibile andare in una certa posizione
    bool canMove(int x, int y) const;

    bool isDead() const;

    // Toglie vita all'entità in input a seconda del proprio attacco
    void attack(Entity *entity);

    void applyDamage(int damage);

    void setDirection(enums::Direction direction);
};