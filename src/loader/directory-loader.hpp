#pragma once 

#include "datastruct/vector.hpp"

namespace loader {
    // questa classe carica la directory degli assets
    // ? serve???? TODO(team): decidere se serve sta cosa
    class AssetsLoader {
      private:
        datastruct::Vector<char *> objectFiles_;
      public:
        AssetsLoader(const char *directory = "assets/");
    }
}; // namespace loader