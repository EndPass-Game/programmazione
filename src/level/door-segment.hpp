#pragma once

#include <ncurses.h>

#include "enums/direction.hpp"
#include "gamestruct/position.hpp"
#include "level/collidable.hpp"
#include "level/displayable-segment.hpp"
#include "level/segment.hpp"
namespace level {

    class DoorSegment : public DisplayableSegment {
      private:
        // direzione rispetto al centro della stanza in cui si trova la porta
        // usato principalmente per dare consistenza ai cambi di stanza
        enums::Direction facingDir_;

        // -1 default per livello inesistente che non porta a nessun livello
        int nextLevelIdx_;

        // true se la porta è aperta, false se chiusa
        bool isOpen_;

        // functione helper per impostare il carattere del segmento
        // @param ch: nuovo carattere di display
        void _setDisplayChar(char ch);

      public:
        DoorSegment();
        DoorSegment(const Segment &segment, enums::Direction facingDir, int nextLevelIdx = -1, bool isOpen = false);

        bool isDoorOpen() const;

        void openDoor();

        void closeDoor();

        void setNextLevelIdx(int nextLevelIdx);

        int getNextLevelIdx() const;

        enums::Direction getFacingDir() const;

        virtual enums::CollisionType getCollisionType() override;
    };
};  // namespace level
