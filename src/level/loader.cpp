#include "level/object-loader.hpp"

namespace level {
    
    Loader::Loader(const char *filename) {
        file_ = fopen(filename, "r");
        isWallTransferred_ = false;
        _loadWalls();
        isDoorTransferred_ = false;
        _loadDoors();
        // TODO(ang|simo): gestire anche gli altri oggetti da loaddare
    }
    
    Loader::~Loader() {
        fclose(file_);
        if (!isWallTransferred_) {
            delete wallSegments_;
        }

        if (!isDoorTransferred_) {
            delete doorSegments_;
        }
    }
    
    void Loader::_loadWalls() {
        int numeroMuri;
        fscanf(file, "%d", &numeroMuri);
        datastruct::Vector<WallSegment *> *walls = new datastruct::Vector<WallSegment *>();
        for(int i = 0; i < numeroMuri; i++) {
            char wallChar;
            int direction;
            Position startPosition;
            int length;
            fscanf(file, "%c (%d,%d) %d %d\n" , &startPosition.x, &startPosition.y , &direction , &length, &wallChar);
            WallSegment *wall = new WallSegment(startPosition, (enums::Direction)direction, length);
            walls.push_back(wall);
        }
        this->wallSegments_ = walls; 
    }

    void Loader::_loadDoors() {
        int numeroPorte;
        fscanf(file, "%d", &numeroPorte);
        datastruct::Vector<DoorSegment *> *doors = new datastruct::Vector<DoorSegment *>();
        for(int i = 0; i < numeroPorte; i++) {
            char doorChar;
            int direction;
            Position startPosition;
            int length;
            fscanf(file, "%c (%d,%d) %d %d\n" , &startPosition.x, &startPosition.y , &direction , &length, &doorChar);
            DoorSegment *door = new DoorSegment(startPosition, (enums::Direction)direction, length);
            doors.push_back(door);
        }
        this->doorSegments_ = doors;
    }

    datastruct::Vector<WallSegment *> *Loader::getLoadedWalls() {
        if (!isWallTransferred_) {
            isWallTransferred_ = true;
            return wallSegments_;
        } else {
            return nullptr;
        }
    }

    datastruct::Vector<DoorSegment *> *Loader::getLoadedDoors() {
        if (!isDoorTransferred_) {
            isDoorTransferred_ = true;
            return doorSegments_;
        } else {
            return nullptr;
        }
    }

}; // namespace level