#pragma once

#include <cstdlib>

#include "collectables/artifact.hpp"
#include "loader/load-object.tpp"

namespace loader {
    class Artifact : public LoadObject<collectables::Artifact> {
      public:
        void load(FILE *file) override;
    };
}  // namespace loader
