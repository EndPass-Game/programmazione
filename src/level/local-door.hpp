#pragma once

#include "level/displayable-segment.hpp"
#include "level/openable.hpp"

namespace level {
    /// Classe utilizzata per rappresentare una porta locale del livello.
    /// a differenza di DoorSegment \link #LocalDoor using another text\endlink
    /// non crea nessun nuovo livello.
    class LocalDoor : public DisplayableSegment, public Openable {
      private:
        int id_;

      public:
        LocalDoor(const Segment &segment, int id, bool isOpen = false);
        int getId();
        void open() override;
        void close() override;
        enums::CollisionType getCollisionType() override;
    };

}  // namespace level
