#pragma once

#include <cstdlib>

#include "collectables/power.hpp"
#include "loader/load-object.hpp"

namespace loader {
    class Power : public LoadObject<collectables::Power> {
      public:
        /**
         * @brief carica gli oggetti per Power
         * 
         * @param file File descriptor da cui caricare il power
         */
        void load(FILE *file) override;
    };
}  // namespace loader