#pragma once

#include <cstdio>  // FILE

#include "level/local-door.hpp"
#include "loader/load-object.tpp"

namespace loader {
    class LocalDoor : public LoadObject<level::LocalDoor> {
      public:
        void load(FILE *file) override;
    };
}  // namespace loader
