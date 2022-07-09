#pragma once 

namespace loader {
    // questa classe carica la directory degli assets
    // ? serve???? TODO(team): decidere se serve sta cosa
    class AssetsLoader {
        datastruct::Vector<char *> objectFiles_;
      public:
        AssetsLoader(const char *directory = "assets/");
    }
}; // namespace loader