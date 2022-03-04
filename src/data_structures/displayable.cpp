#include "displayable.hpp"
#include "position.hpp"


Displayable::Displayable(Position current, char display_char) : 
    last_({-1, -1}),  // all'inizio del gioco non ho un valore vecchio, -1 per non esistenza (fuori schermo)
    current_(current), 
    displayChar_(display_char) {}

void Displayable::movePosition(Position new_position) {
    if (new_position != current_) {
        last_ = current_;
        current_ = new_position;
    }
}

void Displayable::clearLast(WINDOW *win) {
    if (last_ != current_ && last_ != Position{-1,-1}) {
        mvwprintw(win, last_.x, last_.y, " ");
    }
}

void Displayable::render(WINDOW *win) {
    if (last_ != current_) {
        mvwprintw(win, current_.x, current_.y, "%c", displayChar_);
        last_ = current_;
    }
}