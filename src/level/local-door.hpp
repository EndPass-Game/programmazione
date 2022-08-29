#pragma once

#include "level/displayable-segment.hpp"
#include "level/openable.hpp"

namespace level {
    /// Classe utilizzata per rappresentare una porta locale del livello.
    /// a differenza di DoorSegment \link #LocalDoor using another text\endlink
    /// non crea nessun nuovo livello.
    class LocalDoor : public DisplayableSegment, public Openable {
      public:
        LocalDoor(const Segment &segment, bool isOpen = false);
        void open() override;
        void close() override;
    };

}  // namespace level