#pragma once
// TODO(ang)
#include "level/wall-segment.hpp"



namespace level{
    using Door=Displayable;

    class DoorSegment: public WallSegment{
    protected:
        //goToLevel_ == -1 quando è una porta d'uscita che non porta a nessun livello
        int goToLevel_=-1;
        bool isOpen_=false;

    public:
        DoorSegment(Position start_position, enums::Direction direction, int length,int nextLevel,bool isOpen);

        virtual enums::CollisionType getCollisionType() override;
        virtual char chooseWallCharacter(enums::Direction direction,Position pos) override;

    };


}; // namespace level