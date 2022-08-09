#pragma once 

#include <cstdlib>

#include "collectables/power.hpp"
#include "loader/load-object.hpp"

namespace loader {
    class Power: public LoadObject<collectables::Power>{
      public:
        void load(FILE *file) override;
    };
} // namespace loader