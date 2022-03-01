#pragma once
#include "Position.hpp"
#include <climits>
#include <ncurses.h>


class Display{
public:
    Position last;
    Position current;
    char display_char;
    Display(Position current,char display_char);
    void movePosition(Position new_position);
    void clearLast(WINDOW* win);
    void render(WINDOW* win);
};