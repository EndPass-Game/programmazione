#pragma once

#include <ncurses.h>

#include "enums/direction.hpp"
#include "gamestruct/position.hpp"
#include "level/collidable.hpp"
#include "level/displayable-segment.hpp"
#include "level/openable.hpp"
#include "level/segment.hpp"
namespace level {
    class DoorSegment : public DisplayableSegment, public Openable {
      private:
        /// direzione rispetto al centro della stanza in cui si trova la porta
        /// usato principalmente per dare consistenza ai cambi di stanza
        /// poteva succedere che se uscivi da una porta a destra, rientravi a destra
        /// nella prossima stanza, con questi valori, invece se si esce a destra
        /// si rientrerà nella possima stanza a sinsitra.
        enums::Direction facingDir_;

        /// -1 default per livello inesistente che non porta a nessun livello
        int nextLevelIdx_;

      public:
        DoorSegment();
        DoorSegment(const Segment &segment, enums::Direction facingDir, int nextLevelIdx = -1, bool isOpen = false);

        void open() override;

        void close() override;

        void setNextLevelIdx(int nextLevelIdx);

        int getNextLevelIdx() const;

        enums::Direction getFacingDir() const;

        virtual enums::CollisionType getCollisionType() override;
    };
};  // namespace level
