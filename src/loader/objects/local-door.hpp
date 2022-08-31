#pragma once

#include <cstdio>  // FILE

#include "level/local-door.hpp"
#include "loader/load-object.hpp"

namespace loader {
    class LocalDoor : public LoadObject<level::LocalDoor> {
      public:
        /**
         * @brief carica gli oggetti per i door locali dal file
         * 
         * @param file File descriptor da cui caricare i door locali
         */
        void load(FILE *file) override;
    };
}  // namespace loader
