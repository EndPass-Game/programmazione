/*
deve tenere le vite, artefatti, posizione, e items
*/

#pragma once

#include "displayable.hpp"
#include "position.hpp"

class Entity: public Displayable {
  protected:
    int life_;      // quantità di vita
    int attack_;    // danno fatto alle altre entità
    int defense_;   // difesa costante dell'entità
    int shield_;    // difesa temporanea che si può rompere

  public:
    Entity(int life, int attack, int defense = 0, int shield = 0);
    Entity(int life, int attack, int defense, int shield, 
        Position current,
        char displayChar);

    // questa funzione decide tutti i modi per cui le entità che derivano
    // possono muoversi. Si suppone che la logica per muoversi sia diversa
    // da entità a entità, per cui è virtuale
    virtual void move();

    // funzione che fa il check se è possibile andare in una certa posizione
    bool canMove(int x, int y);

    bool isDead();

    // Toglie vita all'entità in input a seconda del proprio attacco
    void attack(Entity *entity);

    void applyDamage(int damage);
};