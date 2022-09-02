#pragma once

#include <cstdlib>

#include "collectables/power.hpp"
#include "loader/load-object.tpp"

namespace loader {
    class Power : public LoadObject<collectables::Power> {
      public:
        void load(FILE *file) override;
    };
}  // namespace loader