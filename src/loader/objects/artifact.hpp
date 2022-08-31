#pragma once

#include <cstdlib>

#include "collectables/artifact.hpp"
#include "loader/load-object.hpp"

namespace loader {
    class Artifact : public LoadObject<collectables::Artifact> {
      public:
        /**
         * @brief carica gli oggetti per Artifact dal file
         * 
         * @param file File descriptor da cui caricare l'artifact
         */
        void load(FILE *file) override;
    };
}  // namespace loader
