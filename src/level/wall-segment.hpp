#pragma once

#include <ncurses.h>

#include "enums/direction.hpp"
#include "enums/wall-angle.hpp"
#include "gamestruct/position.hpp"
#include "level/displayable-segment.hpp"

namespace level {
    /**
     * @brief classe che rappresenta un segmento di muri
     * inoltre i segmenti di muri sono oggetto di collisione per oggetti o entità. e collidable permette ciò
     */
    class WallSegment : public DisplayableSegment {
      private:
        enums::WallAngleType angleType_;

        /**
         * @brief funzione helper che aiuta a decidere il carattere mostrato
         * a seconda della direzione del muro
         *
         * @param direction la direzione su cui andare a decidere il carattere
         * di return
         * @return char il carattere da mostrare
         */
        char _getWallCharacter(enums::Direction direction);

        /**
         * @brief fuzione helper che aiuta a determinare il carattere da mostrare
         * negli angoli `enums::WallType::ANGLE` utilizza la variabile `angleType_` interna
         *
         * @param positionOffset se questo offset deve printare il carattere di `enums::WallType::ANGLE`
         */
        bool _isAngle(int positionOffset);

      public:
        /**
         * @brief segmento vuoto, crea un segmento lungo 0, in posizione 0 di direzione nulla, invalido
         */
        WallSegment();

        /**
         * @brief costruisce un nuovo oggetto Wall Segment
         *
         * @param start_position la posizione di partenza del segmento
         * @param direction la direzione del segmento
         * @param length lunghezza del segmento
         * @param angle tipologia di angolo da usare per il segmento
         */
        WallSegment(Position start_position, enums::Direction direction, int length, enums::WallAngleType angle);

        virtual enums::CollisionType getCollisionType();
    };
}  // namespace level