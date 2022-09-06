#pragma once

#include "enums/direction.hpp"
#include "gamestruct/displayable.hpp"
#include "gamestruct/position.hpp"
#include "manager/level.fwd.h"

/**
 * @brief rappresenta un oggetto che si può muovere mostrabile a schermo
 */
class Movable : public Displayable {
  protected:
    Position nextPosition_;
    enums::Direction lastNotNullDirection_;

    /// Contiene la direzione che dovrà essere intrapresa nel prossimo frame
    enums::Direction direction_;

    /**
     * @brief calcola la prossima posizione
     *
     * @param direction la direzione su cui calcolare la prossima posizione
     * @return Position
     */
    Position _computeNextPosition(enums::Direction direction);

  public:
    Movable(Position current, char displayChar);

    virtual ~Movable() = default;

    void setDirection(enums::Direction direction);

    Position getNextPosition() const;

    enums::Direction getLastNotNullDirection() const;

    /**
     * @brief funzione astratta che gestisce il movimento a singolo frame
     */
    virtual void act(manager::Level *levelManager) = 0;
};