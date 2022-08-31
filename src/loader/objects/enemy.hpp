#pragma once

#include <cstdlib>

#include "entities/enemy.hpp"
#include "loader/load-object.hpp"

namespace loader {
    class Enemy : public LoadObject<entities::Enemy> {
      public:        
        /**
         * @brief carica gli oggetti per Enemy dal file
         * 
         * @param file File descriptor da cui caricare gli enemy
         */
        void load(FILE *file) override;
    };
}  // namespace loader
