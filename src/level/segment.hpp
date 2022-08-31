#pragma once

#include <ncurses.h>

#include "datastruct/vector.tpp"
#include "enums/direction.hpp"
#include "gamestruct/position.hpp"

namespace level {
    // classe che rappresenta un qualunque segmento parallelo a un asse principale x,y
    class Segment {
      protected:
        Position startPosition_;
        // end position è la posizione dell'ultimo muro.
        // È ricavato dalla startPosition_ e la direzione_ e length_, si sceglie
        // di non proporre un costruttore per posizioni iniziali e finali per imporre l'essere parallelo
        // a un asse
        Position endPosition_;
        Position posDirection_;  // versore per indicare la direzione
        int length_;

      public:
        Segment();
        Segment(const Segment &segment);
        Segment(Position start_position, enums::Direction direction, int length);
        virtual ~Segment();

        bool isPositionInSegment(Position pos);
    };  // class segment
};      // namespace level