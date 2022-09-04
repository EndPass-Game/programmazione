#pragma once

#include "level/displayable-segment.hpp"
#include "level/openable.hpp"

namespace level {
    /**
     * @brief Classe utilizzata per rappresentare una porta locale del livello.
     * a differenza di DoorSegment LocalDoor non crea nessun nuovo livello
     * ma è interno al livello
     */
    class LocalDoor : public DisplayableSegment, public Openable {
      private:
        int id_;

      public:
        /**
         * @brief Costruisce un nuovo Local Door object
         *
         * @param segment il segmento per `DisplayableSegment`
         * @param id l'id del door, associato a un Power che lo aprirà
         * @param isOpen lo stato della door
         */
        LocalDoor(const Segment &segment, int id, bool isOpen = false);

        /**
         * @brief Apre la porta (cambia anche il carattere mostrato)
         */
        void open() override;

        /**
         * @brief chiude la porta (cambia anche il carattere mostrato)
         */
        void close() override;

        enums::CollisionType getCollisionType() override;
        int getId();
    };

}  // namespace level
