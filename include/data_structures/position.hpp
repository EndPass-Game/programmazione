#pragma once

class Position
{
public:
    int x;
    int y;

    Position(int x,int y);

    void operator=(const Position& pos);
    bool operator!=(const Position& pos);
    bool operator==(const Position& pos);
    bool operator<(const Position& pos);
};