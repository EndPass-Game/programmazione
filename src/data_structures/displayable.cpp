#include "displayable.hpp"

Displayable::Displayable(Position current, char display_char) : 
    displayChar_(display_char) {
        position=new Changeable<Position>(current);
    }

void Displayable::movePosition(Position new_position) {
    position->setCurrent(new_position);
}

void Displayable::clearLast(WINDOW *win) {
    if (position->isChanged()) {
        mvwprintw(win, position->getLast().x, position->getLast().y, " ");
    }
}

Position Displayable::getPosition(){
    return position->getCurrent();
}
void Displayable::render(WINDOW *win,bool forced) {
    if (position->isChanged() or position->isFirstValue() or forced) {
        mvwprintw(win, position->getCurrent().x, position->getCurrent().y, "%c", displayChar_);
        movePosition(position->getCurrent());
    }
}
Displayable::~Displayable(){
    delete position;
}