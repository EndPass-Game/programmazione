#include "Position.hpp"

Position::Position(int x,int y):x(x),y(y){}

//operation
void Position::operator=(const Position& pos){
    x=pos.x;
    y=pos.y;
}

bool Position::operator!=(const Position& pos){
    return x!=pos.x or y!=pos.y;
}

bool Position::operator==(const Position& pos){
    return x==pos.x and y==pos.y;
}

bool Position::operator<(const Position& pos){
    return x<pos.x and y<pos.y;
}