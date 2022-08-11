#pragma once

#include <mutex>

#include "entities/entity.hpp"
#include "gamestruct/position.hpp"

// Attualmente questa classe contiene un esempio di nemico
// che si muove e attacca il giocatore.
// Dovrebbe essere sostituito da un sistema per gestire ogni
// possibile nemico. (quindi un manager)
// oppure una factory per costruire il nemico specifico
class Enemy : public Entity {
  public:
    Enemy();
    Enemy(Position spawnPos);

    void wander();
};