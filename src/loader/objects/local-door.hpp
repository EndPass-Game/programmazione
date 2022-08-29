#pragma once

#include <cstdio>  // FILE

#include "loader/load-object.hpp"
#include "level/local-door.hpp"

namespace loader {
    class LocalDoor : public LoadObject<level::LocalDoor> {
      public:
        void load(FILE *file) override;
    };
}  // namespace loader
