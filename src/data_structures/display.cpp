#include "Display.hpp"

Display::Display(Position current, char display_char) : display_char(display_char), current(current), last({-1, -1}) {}

void Display::movePosition(Position new_position)
{
    if (new_position!=current)
    {
        last = current;
        current = new_position;
    }
}
void Display::clearLast(WINDOW *win)
{
    if (last != current and last!=Position{-1,-1})
    {
        mvwprintw(win, last.x, last.y, " ");
    }
}
void Display::render(WINDOW *win)
{
    if (last != current)
    {
        mvwprintw(win, current.x, current.y, "%c", display_char);
        last = current;
    }
}