#include "level/object-loader.hpp"

namespace level {
    
    ObjectLoader::ObjectLoader(const char *filename) {
        file_ = fopen(filename, "r");
    }
    
    ObjectLoader::~ObjectLoader() {
        fclose(file_);
    }
    
    
    datastruct::Vector<WallSegment *> *ObjectLoader::loadWalls() {
        int numeroMuri;
        fscanf(file, "%d", &numeroMuri);
        datastruct::Vector<DoorSegment *> *walls();
        for(int i = 0; i < numeroMuri; i++) {
            char wallChar;
            int direction;
            Position startPosition;
            int length;
            fscanf(file, "%c (%d,%d) %d %d\n" , &startPosition.x, &startPosition.y , &direction , &length,&wallChar);
            WallSegment *wall = new WallSegment(startPosition, (enums::Direction)direction, length);
            walls.push_back(wall);
        }
        return walls;
    }
    
}; // namespace level