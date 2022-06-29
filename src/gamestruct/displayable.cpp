#include "gamestruct/displayable.hpp"

Displayable::Displayable() : 
    displayChar_(' ') {
        position_ = new Changeable<Position>(Position(0, 0));
}

Displayable::Displayable(Position current, char display_char) : 
    displayChar_(display_char) {
        position_=new Changeable<Position>(current);
    }

void Displayable::setPosition(Position new_position_) {
    position_->setCurrent(new_position_);
}

void Displayable::clearLast(WINDOW *win) {
    if (position_->isChanged()) {
        mvwprintw(win, position_->getLast().riga, position_->getLast().colonna, " ");
    }
}

Position Displayable::getPosition(){
    return position_->getCurrent();
}
void Displayable::render(WINDOW *win,bool forced) {
    if (position_->isChanged() or position_->isFirstValue() or forced) {
        mvwprintw(win, position_->getCurrent().riga, position_->getCurrent().colonna, "%c", displayChar_);
        setPosition(position_->getCurrent());
    }
}
Displayable::~Displayable(){
    delete position_;
}