#pragma once

#include <ncurses.h>

#include "datastruct/vector.tpp"
#include "enums/direction.hpp"
#include "gamestruct/position.hpp"

namespace level {
    /**
     * @brief  classe che rappresenta un qualunque segmento parallelo a un asse principale x,y
     */
    class Segment {
      protected:
        Position startPosition_;
        /**
         * end position è la posizione dell'ultimo muro.
         * È ricavato dalla startPosition_ e la direzione_ e length_, si sceglie
         * di non proporre un costruttore per posizioni iniziali e finali per imporre l'essere parallelo
         * a un asse
         */
        Position endPosition_;
        Position posDirection_;  // versore per indicare la direzione
        int length_;             // lunghezza del segmento

      public:
        /**
         * @brief Costruisce un nuovo segmento parallelo a un asse INVALIDO
         */
        Segment();

        /**
         * @brief Costruisce un segmento partendo dal segmento passato come parametro
         *
         * @param segment il segmento da cui copiare le informazioni
         */
        Segment(const Segment &segment);

        /**
         * @brief Costruisce un nuovo segmento parallelo a un asse
         *
         * @param startPosition la posizione iniziale del segmento
         * @param direction la direzione del segmento
         * @param length la lunghezza del segmento
         */
        Segment(Position start_position, enums::Direction direction, int length);

        /**
         * @brief distruttore del segmento generato dal compilatore
         */
        virtual ~Segment() = default;

        /**
         * @returns se la posizione è all'interno del segmento ritorna true
         * run in O(1)
         */
        bool isPositionInSegment(Position pos);
    };  // class segment
};      // namespace level