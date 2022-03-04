#pragma once

struct Position {
    int x;
    int y;

    void operator=(const Position& pos);
    bool operator!=(const Position& pos);
    bool operator==(const Position& pos);
    bool operator<(const Position& pos);
};