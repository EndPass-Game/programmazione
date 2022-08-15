#pragma once

#include "enums/direction.hpp"
#include "gamestruct/displayable.hpp"
#include "gamestruct/position.hpp"

// rappresenta un oggetto che si può muovere mostrabile a schermo
class Movable : public Displayable {
  protected:
    Position nextPosition_;
    enums::Direction lastNotNullDirection_;

    // Contiene la direzione che dovrà essere intrapresa nel prossimo frame
    enums::Direction direction_;

    // @param direction la direzione su cui calcolare la prossima posizione
    // calcola la posizione nel prossimo frame
    Position _computeNextPosition(enums::Direction direction);

  public:
    Movable(Position current, char displayChar);  // costruttore
    virtual ~Movable() = default;

    // setter della direzione attuale
    void setDirection(enums::Direction direction);

    // getter per la posizione nel prossimo frame
    Position getNextPosition() const;

    // getter per l'ultima direzione non nulla
    enums::Direction getLastNotNullDirection() const;
};