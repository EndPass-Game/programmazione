#include "loader/objects/wall-segment.hpp"

namespace loader {
    void WallSegment::load(FILE *file) {
        int numeroMuri;
        fscanf(file, "%d", &numeroMuri);
        loadedObjects_.resize(numeroMuri);
        for (int i = 0; i < numeroMuri; i++) {
            int direction;
            Position startPosition;
            int length;
            int angleType;
            fscanf(file, "%d %d %d %d %d\n", &startPosition.riga, &startPosition.colonna, &direction, &length, &angleType);
            level::WallSegment wall = level::WallSegment(startPosition, (enums::Direction) direction, length, (enums::WallAngleType) angleType);
            loadedObjects_[i] = wall;
        }
    }
}  // namespace loader