#pragma once

#include <ncurses.h>

#include "datastruct/vector.tpp"
#include "enums/direction.hpp"
#include "gamestruct/displayable.hpp"
#include "gamestruct/position.hpp"
#include "level/collidable.hpp"
#include "level/segment.hpp"

namespace level {
    /**
     * @brief Classe astratta per rappresentare un segmento di elementi visibili
     */
    class DisplayableSegment : public Segment, public Collidable {
      protected:
        /// vettore dei oggetti mostrato a schermo
        datastruct::Vector<Displayable *> displayables_;

        /**
         * @brief imposta il carattere mostrato per l'intero segmento
         * @param ch: nuovo carattere di display
         */
        void _setDisplayChar(char ch);

      public:
        /**
         * @brief segmento vuoto ed invalido, crea un segmento lungo 0, in posizione 0 di direzione nulla
         */
        DisplayableSegment();

        /**
         * @brief Costruisce un segmento partendo dal segmento passato come parametro
         *
         * @param segment il segmento da cui copiare le informazioni
         */
        DisplayableSegment(const Segment &segment);

        /**
         * @brief crea un segmento di lunghezza length, in posizione startPosition di direzione direction
         * Esempio: DisplayableSegment(Position(0, 0), enums::Direction::RIGHT, 10)
         * crea un segmento di 10 muri in posizione (0, 0) e direzione a destra che printata a schermo è
         * OOOOOOOOOO (o comunque qualunque carattere di default per il muro)
         */
        DisplayableSegment(Position start_position, enums::Direction direction, int length);

        /**
         * @brief Elimina tutti i displayables del segmento
         */
        virtual ~DisplayableSegment();

        /**
         * @brief renderizza i displayables del segmento
         *
         * @param win la window su cui renderizzare
         * @param force se true, renderizza anche gli elementi che sono ancora gli stessi
         * altrimenti fa lazy rendering, non toccando nessun elemento che rimane lo stesso
         */
        virtual void render(WINDOW *win, bool force);

        /**
         * @brief Cancella tutti gli elementi del segmento da schermo
         *
         * @param win la window su cui cancellare
         */
        virtual void clear(WINDOW *win);
    };
};  // namespace level
