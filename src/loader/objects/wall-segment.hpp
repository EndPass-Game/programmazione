#pragma once

#include <cstdlib>

#include "level/wall-segment.hpp"
#include "loader/load-object.hpp"

namespace loader {
    class WallSegment : public LoadObject<level::WallSegment> {
      public:
        /**
         * @brief carica gli oggetti per wallsegment
         * 
         * @param file File descriptor da cui caricare di wallsegment
         */
        void load(FILE *file) override;
    };
}  // namespace loader