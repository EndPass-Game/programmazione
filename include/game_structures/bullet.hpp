#pragma once

#include "displayable.hpp"
#include "direction.hpp"
#include "entity.hpp"
#include "position.hpp"

// 1. Deve sapere se si deve distruggere o meno
// 2. Deve essere updatato dal displayer e muoversi 
// 3. Deve fare danno se colpisce

class Bullet: public Displayable {
  private:
    enums::Direction direction_;
    int damage_;

  public:
    Bullet(Position position, enums::Direction direction);

    // TODO(SIMO): Funzione che ritorna true se ha colpito qualcosa
    // e false altrimenti, deve essere gestito dal collision detector
    bool hasHit();

    // TODO(SIMO):
    void handleEntityHit(Entity *entity);

    void move();
};